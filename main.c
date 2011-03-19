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
#define     LED1                  BIT1
#define     LED2                  BIT2
#define     LED3                  BIT3
#define     LED4                  BIT4
#define     LED5                  BIT5
#define     LED6                  BIT6
#define     LED7                  BIT7
#define     ALL_LEDS              (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7)
#define     LED_DIR               P1DIR
#define     LED_OUT               P1OUT
//
//blink or rot
//#define BLINK


void initLEDs(void) {
  LED_DIR |= ALL_LEDS;
  LED_OUT |= ALL_LEDS;
}

int n = 0;

int main(void) {

  WDTCTL = WDTPW + WDTHOLD;	// Stop WDT

  initLEDs();		//Setup LEDs

  BCSCTL3 |= LFXT1S_2;	//Set ACLK to use internal VLO (12 kHz clock)

  TACTL = TASSEL_1 | MC_1;	//Set TimerA to use auxiliary clock in UP mode
  TACCTL0 = CCIE;	//Enable the interrupt for TACCR0 match
  TACCR0 = 3000;	/*Set TACCR0 which also starts the timer. At
				12 kHz, counting to 12000 should output
				an LED change every 1 second. Try this
				out and see how inaccurate the VLO can be */

  WRITE_SR(GIE);	//Enable global interrupts

  while(1) {
	//Loop forever, interrupts take care of the rest
  }
}

/* Interrupt routine for having led1 flash n times, where n
 * is defined by setting it equal to the bit number. Just a
 * method for demonstrating bit twiddling, and ensurin
 * MSB/LSB things */

int m = 0;
interrupt(TIMERA0_VECTOR) TIMERA0_ISR(void) {
    if (n==0) {
        TACCR0 = 5000;
        LED_OUT = ALL_LEDS;
        n = LED3;
    } else if (m == 0) {
        LED_OUT = 0;
        m++;
        m %= 2;
    } else {
        LED_OUT = 0;
        LED_OUT = LED1;
        m++;
        m %=2;
        n--;
    }
}

/*
 * An intterupt routine that turns on each pin sequentially, then all at once.
 */

 /*
interrupt(TIMERA0_VECTOR) TIMERA0_ISR(void) {
  n++;
  n = n % 9;


 switch (n) {
    case 0:
      LED_OUT = LED0;
      break;
    case 1:
      LED_OUT = LED1;
      break;
    case 2:
      LED_OUT = LED2;
      break;
    case 3:
      LED_OUT = LED3;
      break;
    case 4:
      LED_OUT = LED4;
      break;
    case 5:
      LED_OUT = LED5;
      break;
    case 6:
      LED_OUT = LED6;
      break;
    case 7:
      LED_OUT = LED7;
      break;
    default:
      LED_OUT = ALL_LEDS;
      break;
  }

}
*/

