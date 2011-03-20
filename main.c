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

#include <io.h>
#include <signal.h>
#include "reg.h"
#include "morse.h"

#define     LED0                  BIT0
#define     LED1                  BIT6
#define     LED_DIR               P1DIR
#define     LED_OUT               P1OUT

#define     MASK_N(n)  ( ~(~0<<n))

void initLEDs(void) {
  LED_DIR |= LED0 + LED1;
  LED_OUT = LED1;
}


struct SR output;

int to_cbr(int data, int bits, unsigned long long *data_out, int *bits_out) {
	*bits_out = 0;
	*data_out = 0;

	while (bits > 0) {
		//convert 1 to
		if ((data & 1)) {
			*data_out = *data_out << DASH;
			*data_out |= MASK_N(DASH);
			*bits_out += DASH;
		} else {
			*data_out = *data_out << DOT;
			*data_out |= MASK_N(DOT);
			*bits_out += DOT;
	  }
		//add the space between signals, OFF is 0, so no setting of bits,
		//just shifting 0 in
		*data_out = *data_out << OFF;
		*bits_out += OFF;
		bits--;
		data = data >> 1;
	}
	if (*bits_out < (sizeof(*data_out) * 8)) {
		return 1;
	} else {
		return 0;
	}
}

void bockwrite(struct SR *output, unsigned long long data, int bits) {
	while (1) {
		if (SR_WRITEABLE(output, bits)) {
			SR_write(output, data, bits);
			return;
		}
	}
}

int main(void) {
	char *string = "hello world\0";
	unsigned char waiting = 0;
	int i = 0;
	short started = 0;
	int cbrbits=0;
	unsigned long long cbrdata=0;
	unsigned char mp;


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

	SR_init(&output);

  while(1) {
		// have data ready to put in the output struct
		if (!waiting) {
			if ((*(string+ i) == ' ') || (*(string + i) == '\0')) {
				cbrdata = 0;
				cbrbits = 0;
			} else {
				mp = convert_ascii(*(string + i));
				to_cbr(M_VAL(mp), M_SIZE(mp), &cbrdata, &cbrbits);
			}
			if (*(string + i) == '\0') {
				i = 0;
			} else {
				i++;
			}
			waiting = 1;
		}

		// if there is room, put the stuff in the register
		if (waiting) {
			if (cbrbits && SR_WRITEABLE(&output,cbrbits+LS)) {
				SR_write(&output, cbrdata, cbrbits);
				//letter pause
				SR_write(&output, 0x0, LS);
				waiting = 0;

			} else if (SR_WRITEABLE(&output, WS)){
				// must be space or \0, put in WS
				SR_write(&output, 0x0, WS);
				waiting = 0;
			}
			LED_OUT &= ~LED1;
		} else { LED_OUT |= LED1;}
		//if (!started) {
		//	started = 1;
		//	TACCR0 = 3000;
		//}
		//if(*(string + 0) == 'h') LED_OUT &= ~LED1;

  }
}

/* Interrupt routine for having led1 flash n times, where n
 * is defined by setting it equal to the bit number. Just a
 * method for demonstrating bit twiddling, and ensurin
 * MSB/LSB things */

interrupt(TIMERA0_VECTOR) TIMERA0_ISR(void) {
	if (SR_read(&output)) {
		LED_OUT |= LED0;
	} else {
		LED_OUT &= ~LED0;
	}
	return;
}


