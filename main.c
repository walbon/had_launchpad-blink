/*
Copyright (c) 2010 - Mike Szczys

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

//#include <msp430x20x2.h>  <-taken care of by including io.h and setting -mmcu=msp430x2012 in cflags
	/* It's interesting to note that this is not the header
		file for the chip we are using. This source code
		is intended for the MSP430G2231 but there's no
		header file for that specific ship. It apprears
		That the MPS430x2012 is closely related and
		I haven't observed any problems with using this
		header file. */
//#include <msp430g2231.h>
#include <io.h>
#include <signal.h>

#define     LED0                  BIT0
#define     LED1                  BIT6
#define     LED_DIR               P1DIR
#define     LED_OUT               P1OUT
//
//blink or rot
//#define BLINK


void initLEDs(void) {
  LED_DIR |= LED0 + LED1 + BIT7;	//Set LED pins as outputs
  LED_OUT |= LED0 + LED1;	//Turn on both LEDs
}

int n = 0;

int main(void) {

  WDTCTL = WDTPW + WDTHOLD;	// Stop WDT

  initLEDs();		//Setup LEDs

  BCSCTL3 |= LFXT1S_2;	//Set ACLK to use internal VLO (12 kHz clock)

  TACTL = TASSEL_1 | MC_1;	//Set TimerA to use auxiliary clock in UP mode
  TACCTL0 = CCIE;	//Enable the interrupt for TACCR0 match
  TACCR0 = 1000;	/*Set TACCR0 which also starts the timer. At
				12 kHz, counting to 12000 should output
				an LED change every 1 second. Try this
				out and see how inaccurate the VLO can be */

  WRITE_SR(GIE);	//Enable global interrupts

  while(1) {
	//Loop forever, interrupts take care of the rest
  }
}

interrupt(TIMERA0_VECTOR) TIMERA0_ISR(void) {
      LED_OUT ^= (LED0 +  BIT7);	//turn on

/*
#ifndef BLINK
  n += 1;
  n = n % 3;
#ifdef FORWARD
  if (n == 0) {
    LED_OUT ^= (LED0);
  } else if (n ==1) {
    LED_OUT ^= (LED1);
  } else {
      LED_OUT |= (LED0 + LED1);	//turn on
  }
#else
  if (n == 2) {
    LED_OUT ^= (LED0);
  } else if (n ==1) {
    LED_OUT ^= (LED1);
  } else {
      LED_OUT |= (LED0 + LED1);	//turn on
  }
#endif
#endif
*/
}


