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

#include <io.h>
#include <signal.h>
#include <sys/inttypes.h>
#include "reg.h"
#include "morse.h"

#define     LED0                  BIT0
#define     LED1                  BIT6
#define     LED_DIR               P1DIR
#define     LED_OUT               P1OUT

#define     TIMER                 1000

void initLEDs(void) {
  LED_DIR |= LED0 + LED1;
  LED_OUT = LED1;
}


struct SR output;
volatile int wait = 0;

int to_cbr(uint8_t data, uint8_t bits, srdata *data_out, uint8_t *bits_out) {
	*bits_out = 0;
	*data_out = 0;

	while (1) {
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
		// for next loop
		bits--;
		data = data >> 1;
		if (bits > 0) { //loop!
			//add the space between signals (output off, 0), so no setting of bits,
			//just shifting 0 in, OFF translates to the number of units of no signal
			*data_out = *data_out << OFF;
			*bits_out += OFF;
		} else { //done
			break;
		}
	}
	if (*bits_out < (sizeof(*data_out) * 8)) {
		return 1;
	} else {
		return 0;
	}
}

void blockwrite(struct SR *sr, srdata data, uint8_t bits) {
	if (!SR_WRITEABLE(sr, bits)) {
		wait = (bits + sr->pos) - ((sizeof(sr->data)*8) - 1);
		LED_OUT &= ~LED1;
	}
	while (wait) {
		//loop till something else makes wait go to 0

	}
	if (1) LED_OUT |= LED1;
	SR_write(sr, data, bits);
	return;
}

inline void magic() {
	WDTCTL = WDTPW + WDTHOLD;	// Stop WDT


	BCSCTL3 |= LFXT1S_2;	//Set ACLK to use internal VLO (12 kHz clock)

	TACTL = TASSEL_1 | MC_1;	//Set TimerA to use auxiliary clock in UP mode
	TACCTL0 = CCIE;	//Enable the interrupt for TACCR0 match
	TACCR0 = TIMER;	/*Set TACCR0 which also starts the timer. At
				12 kHz, counting to 12000 should output
				an LED change every 1 second. Try this
				out and see how inaccurate the VLO can be */

	WRITE_SR(GIE);	//Enable global interrupts
	return;
}

int main(void) {
	char *string = "hello judith pond\0";
	int i = 0;
	uint8_t cbrbits = 0;
	srdata cbrdata = 0;
	uint8_t mp;

	// setup stuff i don't fully understand
	magic();
	initLEDs();		//Setup LEDs

	SR_init(&output);

	while(1) {
		// have data ready to put in the output struct
		if ((*(string + i) == ' ')) {
			blockwrite(&output, 0x0, WS);
			i++;
		} else if((*(string + i) == '\0')){
			blockwrite(&output, 0x0, WS);
			i = 0;
		} else {
			mp = convert_ascii(*(string + i));
			to_cbr(M_VAL(mp), M_SIZE(mp), &cbrdata, &cbrbits);
			blockwrite(&output, cbrdata, cbrbits);
			blockwrite(&output, 0x0, LS);
			i++;
		}
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
	wait--;
	return;
}
