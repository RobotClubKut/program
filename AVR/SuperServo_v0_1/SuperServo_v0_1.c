#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "io_bitfield.h"
#include "SuperServo.h"


/** Pulses a pin - high then low. */
#define pulse_pin(port, pin)   port |= _BV(pin); port &= ~_BV(pin)

/** This will be true (!= 0) if update was just called and the data has not
    been latched in yet. */
volatile uint8_t tlc_needXLAT;

/** Some of the extened library will need to be called after a successful
    update. */
volatile void (*tlc_onUpdateFinished)(void);

uint8_t tlc_GSData[NUM_TLCS * 24];

/** Don't add an extra SCLK pulse after switching from dot-correction mode. */
static uint8_t firstGSInput;

ISR(TIMER1_OVF_vect)
{
    disable_XLAT_pulses();
    clear_XLAT_interrupt();
    tlc_needXLAT = 0;
    if (tlc_onUpdateFinished) {
        sei();
        tlc_onUpdateFinished();
    }
}


int main(void)
{
	uint16_t x=0;

	Tlc5940_init(2000);
	while(1)
	{
	/*
		Tlc5940_setAll(x);
		Tlc5940_update();
		_delay_ms(500);
		if(x<4096)
			x += 500;
		else
			x = 0;
	*/
	}
	return 0;
}

void Tlc5940_init(uint16_t initialValue)
{
	XLAT_DDR |= _BV(XLAT_PIN);
    BLANK_DDR |= _BV(BLANK_PIN);
    GSCLK_DDR |= _BV(GSCLK_PIN);

    VPRG_DDR |= _BV(VPRG_PIN);
    VPRG_PORT &= ~_BV(VPRG_PIN);  // grayscale mode (VPRG low)


    XERR_DDR &= ~_BV(XERR_PIN);   // XERR as input
    XERR_PORT |= _BV(XERR_PIN);   // enable pull-up resistor

	BLANK_PORT |= _BV(BLANK_PIN); // leave blank high (until the timers start)

	tlc_shift8_init();

    Tlc5940_setAll(initialValue);

    Tlc5940_update();
	disable_XLAT_pulses();
    clear_XLAT_interrupt();
    tlc_needXLAT = 0;
    pulse_pin(XLAT_PORT, XLAT_PIN);

    /* Timer Setup */

    /* Timer 1 - BLANK / XLAT */
    TCCR1A = _BV(COM1B1);  // non inverting, output on OC1B, BLANK
    TCCR1B = _BV(WGM13);   // Phase/freq correct PWM, ICR1 top
    OCR1A = 1;             // duty factor on OC1A, XLAT is inside BLANK
    OCR1B = 2;             // duty factor on BLANK (larger than OCR1A (XLAT))
    ICR1 = TLC_PWM_PERIOD; // see tlc_config.h

    /* Timer 0 - GSCLK */
    TCCR0A = _BV(COM0B1)      // set on BOTTOM, clear on OCR0A (non-inverting),
                              // output on OC0B
           | _BV(WGM01)       // Fast pwm with OCR0A top
           | _BV(WGM00);      // Fast pwm with OCR0A top
    TCCR0B = _BV(WGM02);      // Fast pwm with OCR0A top
    OCR0B = 0;                // duty factor (as short a pulse as possible)
    OCR0A = TLC_GSCLK_PERIOD; // see tlc_config.h
    TCCR0B |= _BV(CS00);      // no prescale, (start pwm output)

    TCCR1B |= _BV(CS10);      // no prescale, (start pwm output)
    Tlc5940_update();
}
/** Sets all channels to value.
    \param value grayscale value (0 - 4095) */
void Tlc5940_setAll(uint16_t value)
{
    uint8_t firstByte = value >> 4;
    uint8_t secondByte = (value << 4) | (value >> 8);
    uint8_t *p = tlc_GSData;
    while (p < tlc_GSData + NUM_TLCS * 24) {
        *p = firstByte;
		p++;
        *p = secondByte;
		p++;
        *p = (uint8_t)value;
		p++;
    }
}
/** Clears the grayscale data array, #tlc_GSData, but does not shift in any
    data.  This call should be followed by update() if you are turning off
    all the outputs. */
void Tlc5940_clear(void)
{
    Tlc5940_setAll(0);
}

/** Shifts in the data from the grayscale data array, #tlc_GSData.
    If data has already been shifted in this grayscale cycle, another call to
    update() will immediately return 1 without shifting in the new data.  To
    ensure that a call to update() does shift in new data, use
    \code while(Tlc.update()); \endcode
    or
    \code while(tlc_needXLAT); \endcode
    \returns 1 if there is data waiting to be latched, 0 if data was
             successfully shifted in */
uint8_t Tlc5940_update(void)
{
    if (tlc_needXLAT) {
        return 1;
    }
    disable_XLAT_pulses();
    if (firstGSInput) {
        // adds an extra SCLK pulse unless we've just set dot-correction data
        firstGSInput = 0;
    } else {
        pulse_pin(SCLK_PORT, SCLK_PIN);
    }
    uint8_t *p = tlc_GSData;
    while (p < (tlc_GSData + NUM_TLCS * 24)) {
        tlc_shift8(*(p++));
        tlc_shift8(*(p++));
        tlc_shift8(*(p++));
    }
    tlc_needXLAT = 1;
    enable_XLAT_pulses();
    set_XLAT_interrupt();
    return 0;
}

/** Sets channel to value in the grayscale data array, #tlc_GSData.
    \param channel (0 to #NUM_TLCS * 16 - 1).  OUT0 of the first TLC is
           channel 0, OUT0 of the next TLC is channel 16, etc.
    \param value (0-4095).  The grayscale value, 4095 is maximum.
    \see get */
void Tlc5940_set(TLC_CHANNEL_TYPE channel, uint16_t value)
{
    TLC_CHANNEL_TYPE index8 = (NUM_TLCS * 16 - 1) - channel;
    uint8_t *index12p = tlc_GSData + ((((uint16_t)index8) * 3) >> 1);
    if (index8 & 1) { // starts in the middle
                      // first 4 bits intact | 4 top bits of value
        *index12p = (*index12p & 0xF0) | (value >> 8);
                      // 8 lower bits of value
        *(++index12p) = value & 0xFF;
    } else { // starts clean
                      // 8 upper bits of value
        *(index12p++) = value >> 4;
                      // 4 lower bits of value | last 4 bits intact
        *index12p = ((uint8_t)(value << 4)) | (*index12p & 0xF);
    }
}

/** Gets the current grayscale value for a channel
    \param channel (0 to #NUM_TLCS * 16 - 1).  OUT0 of the first TLC is
           channel 0, OUT0 of the next TLC is channel 16, etc.
    \returns current grayscale value (0 - 4095) for channel
    \see set */
uint16_t Tlc5940_get(TLC_CHANNEL_TYPE channel)
{
    TLC_CHANNEL_TYPE index8 = (NUM_TLCS * 16 - 1) - channel;
    uint8_t *index12p = tlc_GSData + ((((uint16_t)index8) * 3) >> 1);
    return (index8 & 1)? // starts in the middle
            (((uint16_t)(*index12p & 15)) << 8) | // upper 4 bits
            *(index12p + 1)                       // lower 8 bits
        : // starts clean
            (((uint16_t)(*index12p)) << 4) | // upper 8 bits
            ((*(index12p + 1) & 0xF0) >> 4); // lower 4 bits
    // that's probably the ugliest ternary operator I've ever created.
}

/** \addtogroup ReqVPRG_ENABLED
    From the \ref CoreFunctions "Core Functions":
    - \link Tlc5940::setAllDC Tlc.setAllDC(uint8_t value(0-63)) \endlink - sets
      all the dot correction data to value */
/* @{ */

/** Sets the dot correction for all channels to value.  The dot correction
    value correspondes to maximum output current by
    \f$\displaystyle I_{OUT_n} = I_{max} \times \frac{DCn}{63} \f$
    where
    - \f$\displaystyle I_{max} = \frac{1.24V}{R_{IREF}} \times 31.5 =
         \frac{39.06}{R_{IREF}} \f$
    - DCn is the dot correction value for channel n
    \param value (0-63) */
void Tlc5940_setAllDC(uint8_t value)
{
    tlc_dcModeStart();

    uint8_t firstByte = value << 2 | value >> 4;
    uint8_t secondByte = value << 4 | value >> 2;
    uint8_t thirdByte = value << 6 | value;

    for (TLC_CHANNEL_TYPE i = 0; i < NUM_TLCS * 12; i += 3) {
        tlc_shift8(firstByte);
        tlc_shift8(secondByte);
        tlc_shift8(thirdByte);
    }
    pulse_pin(XLAT_PORT, XLAT_PIN);

    tlc_dcModeStop();
}

/* @} */


/** Checks for shorted/broken LEDs reported by any of the TLCs.
    \returns 1 if a TLC is reporting an error, 0 otherwise. */
uint8_t Tlc5940_readXERR(void)
{
    return ((XERR_PINS & _BV(XERR_PIN)) == 0);
}


/* @} */

#if DATA_TRANSFER_MODE == TLC_BITBANG

/** Sets all the bit-bang pins to output */
void tlc_shift8_init(void)
{
    SIN_DDR |= _BV(SIN_PIN);   // SIN as output
    SCLK_DDR |= _BV(SCLK_PIN); // SCLK as output
    SCLK_PORT &= ~_BV(SCLK_PIN);
}

/** Shifts a byte out, MSB first */
void tlc_shift8(uint8_t byte)
{
    for (uint8_t bit = 0x80; bit; bit >>= 1) {
        if (bit & byte) {
            SIN_PORT |= _BV(SIN_PIN);
        } else {
            SIN_PORT &= ~_BV(SIN_PIN);
        }
        pulse_pin(SCLK_PORT, SCLK_PIN);
    }
}

#elif DATA_TRANSFER_MODE == TLC_SPI

/** Initializes the SPI module to double speed (f_osc / 2) */
void tlc_shift8_init(void)
{
    SIN_DDR    |= _BV(SIN_PIN);    // SPI MOSI as output
    SCLK_DDR   |= _BV(SCLK_PIN);   // SPI SCK as output
    TLC_SS_DDR |= _BV(TLC_SS_PIN); // SPI SS as output

    SCLK_PORT &= ~_BV(SCLK_PIN);

    SPSR = _BV(SPI2X); // double speed (f_osc / 2)
    SPCR = _BV(SPE)    // enable SPI
         | _BV(MSTR);  // master mode
}

/** Shifts out a byte, MSB first */
void tlc_shift8(uint8_t byte)
{
    SPDR = byte; // starts transmission
    while (!(SPSR & _BV(SPIF)))
        ; // wait for transmission complete
}

#endif


/** Switches to dot correction mode and clears any waiting grayscale latches.*/
void tlc_dcModeStart(void)
{
    disable_XLAT_pulses(); // ensure that no latches happen
    clear_XLAT_interrupt(); // (in case this was called right after update)
    tlc_needXLAT = 0;
    VPRG_PORT |= _BV(VPRG_PIN); // dot correction mode
}

/** Switches back to grayscale mode. */
void tlc_dcModeStop(void)
{
    VPRG_PORT &= ~_BV(VPRG_PIN); // back to grayscale mode
    firstGSInput = 1;
}
