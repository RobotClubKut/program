

#ifndef SUPERSERVO_H
#define SUPERSERVO_H


#include <stdint.h>

#include <stdint.h>


#define TLC_BITBANG        1
/** Use the much faster hardware SPI module */
#define TLC_SPI            2

/* ------------------------ START EDITING HERE ----------------------------- */

/** Number of TLCs daisy-chained.  To daisy-chain, attach the SOUT (TLC pin 17)
    of the first TLC to the SIN (TLC pin 26) of the next.  The rest of the pins
    are attached normally.
    \note Each TLC needs it's own IREF resistor */
#define NUM_TLCS    1

/** Determines how data should be transfered to the TLCs.  Bit-banging can use
    any two i/o pins, but the hardware SPI is faster.
    - Bit-Bang = TLC_BITBANG
    - Hardware SPI = TLC_SPI (default) */
#define DATA_TRANSFER_MODE    TLC_SPI


/* Set DATA_TRANSFER_MODE to TLC_BITBANG and change the pins below if you need
   to use different pins for sin and sclk.  The defaults are defined in
   pinouts/ATmega_xx8.h for most Arduino's. */

#if DATA_TRANSFER_MODE == TLC_BITBANG
/** SIN (TLC pin 26) */
#define SIN_PIN        PB3
#define SIN_PORT       PORTB
#define SIN_DDR        DDRB
/** SCLK (TLC pin 25) */
#define SCLK_PIN       PB5
#define SCLK_PORT      PORTB
#define SCLK_DDR       DDRB
#endif


/** If more than 16 TLCs are daisy-chained, the channel type has to be uint16_t.
    Default is uint8_t, which supports up to 16 TLCs. */
#define TLC_CHANNEL_TYPE    uint8_t

/** Determines how long each PWM period should be, in clocks.
    \f$\displaystyle f_{PWM} = \frac{f_{osc}}{2 * TLC\_PWM\_PERIOD} Hz \f$
    \f$\displaystyle TLC\_PWM\_PERIOD = \frac{f_{osc}}{2 * f_{PWM}} \f$
    This is related to TLC_GSCLK_PERIOD:
    \f$\displaystyle TLC\_PWM\_PERIOD =
       \frac{(TLC\_GSCLK\_PERIOD + 1) * 4096}{2} \f$
    \note The default of 8192 means the PWM frequency is 976.5625Hz */
#define TLC_PWM_PERIOD    8192

/** Determines how long each period GSCLK is.
    This is related to TLC_PWM_PERIOD:
    \f$\displaystyle TLC\_GSCLK\_PERIOD =
       \frac{2 * TLC\_PWM\_PERIOD}{4096} - 1 \f$
    \note Default is 3 */
#define TLC_GSCLK_PERIOD    3

/** Enables/disables VPRG (TLC pin 27) functionality.  If you need to set dot
    correction data, this needs to be enabled.
    - 0 VPRG is not connected.  <em>TLC pin 27 must be grounded!</em> (default)
    - 1 VPRG is connected
    \note VPRG to GND inputs grayscale data, VPRG to Vcc inputs dot-correction
          data */

/** VPRG (TLC pin 27) */
#define VPRG_PIN        PD7
#define VPRG_PORT       PORTD
#define VPRG_DDR        DDRD


#define XERR_PIN        PC0
#define XERR_PORT       PORTC
#define XERR_DDR        DDRC
#define XERR_PINS       PINC

#define TLC_SS_PIN       PB2
#define TLC_SS_DDR       DDRB

/** OC1A (Arduino digital pin 9) -> XLAT (TLC pin 24) */
#define XLAT_PIN     PB1
#define XLAT_PORT    PORTB
#define XLAT_DDR     DDRB

/** OC1B (Arduino digital pin 10) -> BLANK (TLC pin 23) */
#define BLANK_PIN    PB2
#define BLANK_PORT   PORTB
#define BLANK_DDR    DDRB

/** OC0B (Arduino digital pin 3) -> GSCLK (TLC pin 18) */
#define GSCLK_PIN    PD5
#define GSCLK_PORT   PORTD
#define GSCLK_DDR    DDRD
/* ------------------------- STOP EDITING HERE ----------------------------- */

#if DATA_TRANSFER_MODE == TLC_SPI
/** SIN (TLC pin 26) */
#define SIN_PIN        PB3
#define SIN_PORT       PORTB
#define SIN_DDR        DDRB
/** SCLK (TLC pin 25) */
#define SCLK_PIN       PB5
#define SCLK_PORT      PORTB
#define SCLK_DDR       DDRB
#endif



#if !(DATA_TRANSFER_MODE == TLC_BITBANG \
 || DATA_TRANSFER_MODE == TLC_SPI)
#error "Invalid DATA_TRANSFER_MODE specified, see DATA_TRANSFER_MODE"
#endif

/* Various Macros */

/** Arranges 2 grayscale values (0 - 4095) in the packed array format (3 bytes).
    This is for array initializers only: the output is three comma seperated
    8-bit values. */
#define GS_DUO(a, b)    ((a) >> 4), ((a) << 4) | ((b) >> 8), (b)


/** Arranges 4 dot correction values (0 - 63) in the packed array format.
    \see setDCtoProgmemArray */
#define DC_QUARTET(a, b, c, d)   ((a) << 2) | ((b) >> 4), \
                                 ((b) << 4) | ((c) >> 2), \
                                 ((c) << 6) | (d)



/** Enables the Timer1 Overflow interrupt, which will fire after an XLAT
    pulse */
#define set_XLAT_interrupt()    TIFR1 |= _BV(TOV1); TIMSK1 = _BV(TOIE1)
/** Disables any Timer1 interrupts */
#define clear_XLAT_interrupt()  TIMSK1 = 0

/** Enables the output of XLAT pulses */
#define enable_XLAT_pulses()    TCCR1A = _BV(COM1A1) | _BV(COM1B1)
/** Disables the output of XLAT pulses */
#define disable_XLAT_pulses()   TCCR1A = _BV(COM1B1)

extern volatile uint8_t tlc_needXLAT;
extern volatile void (*tlc_onUpdateFinished)(void);
extern uint8_t tlc_GSData[NUM_TLCS * 24];

void Tlc5940_init(uint16_t initialValue);

void Tlc5940_clear(void);

uint8_t Tlc5940_update(void);

void Tlc5940_set(TLC_CHANNEL_TYPE channel, uint16_t value);

uint16_t Tlc5940_get(TLC_CHANNEL_TYPE channel);

void Tlc5940_setAll(uint16_t value);

void setAllDC(uint8_t value);

uint8_t readXERR(void);


void tlc_shift8_init(void);
void tlc_shift8(uint8_t byte);

void tlc_dcModeStart(void);
void tlc_dcModeStop(void);


#endif

