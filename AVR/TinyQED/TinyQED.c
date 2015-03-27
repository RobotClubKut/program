/***************************************************************************
* File              : TinyQED
* Compiler          : AVRstudio 4
* Revision          : 1.0
* Date              : Tuesday, June 11, 2007
* Revised by        : Adriaan Swanepoel
*                   : Adapted from Dan Gates I2C analogue slave
*					  http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=51467
*                     and Jim Remington's Quadrature encoder for the O 
*					  http://forum.pololu.com/viewtopic.php?t=484
*
* Target device		: ATtiny45
*
* Connections
*                               ATTiny45
*                 +--------------------------------+
*                 | 1 pb5 reset              VCC 8 | VCC
*         Motor A | 2 pb3                    pb2 7 | SCL
*         Motor B | 3 pb4                    pb1 6 | 
*             GND | 4 GND                    pb0 5 | SDA
*                 +--------------------------------+
****************************************************************************/

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "usiTwiSlave.h"

#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

union doublebyte
{
  unsigned int value;
  unsigned char bytes[2];
};

union doublebyte enc_pos;
unsigned char enc_dir;
unsigned char enc_last=0;
unsigned char enc_now;

/******************************************************************************
 *
 * 
 *
 * Description:	
 * ARGS:		none
 * RETURN:		none
 *
 *****************************************************************************/
ISR (PCINT0_vect)
{
  enc_now = (PINB & (3 << 3)) >> 3;                //read the port pins and shift result to bottom bits
  enc_dir = (enc_last & 1) ^ ((enc_now & 2) >> 1); //determine direction of rotation
  
  if(enc_dir == 0) 
  	enc_pos.value++; 
 
  	else   

  		enc_pos.value--;        //update encoder position
  
  enc_last = enc_now;     //remember last state
}


/******************************************************************************
 *
 * main
 *
 * Description:	Where it all starts...
 * ARGS:		none
 * RETURN:		none
 *
 *****************************************************************************/
int main(void)
{
  unsigned char temp;
  enc_pos.value = 0;

  PCMSK |= (1 << PCINT3); // tell pin change mask to listen to pin2
  GIMSK |= (1 << PCIE);   // enable PCINT interrupt in the general interrupt mask
  
  sei();

  cbi(DDRB, DDB3);        // PB3 set up as input
  cbi(DDRB, DDB4);        // PB4 set up as input
  sbi(PORTB, PB3);	      // Set PB3 internal pullup
  sbi(PORTB, PB4);	      // Set PB4 internal pullup

  //unsigned char slaveAddress = 0x26;
  //unsigned char slaveAddress = 0x2E;	  
  //unsigned char slaveAddress = 0x36;
  unsigned char slaveAddress = 0x3E;

  usiTwiSlaveInit(slaveAddress);

  for (;;)
  {
    if (usiTwiDataInReceiveBuffer())
    {
	  temp = usiTwiReceiveByte();
     
	  //which register requested
	  //1..9   Reserved Commands
	  //10..19 Reserved Data
	  switch (temp)
	  {
	             //Reset the counter
		case 1 : enc_pos.value = 0; 
		         break; 

			     //Send the counter
		case 10: usiTwiTransmitByte(enc_pos.bytes[0]);
				 usiTwiTransmitByte(enc_pos.bytes[1]); 
		         break;
		
		default : //Do nothing
		          break;
	  }	  
    }

	asm volatile ("NOP"::);
  }
}

