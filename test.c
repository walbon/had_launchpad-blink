#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <signal.h>
#include "morse.h"
#include "reg.h"

volatile int wait = 0;
struct SR output;
struct itimerval mytimer;

void pbin(srdata val) {
	int x = sizeof(val) * 8;
	while(x > 0) {
		printf("%d", val & 1);
		val >>= 1;
		x --;
	}
}

void blockwrite(struct SR *sr, srdata data, uint8_t bits) {
	//printf("blockwrite: ");
	//pbin(data);
	//printf(", %d\n", bits);
	if (!SR_WRITEABLE(sr, bits)) {
		wait = (bits + sr->pos) - ((sizeof(sr->data)*8)-1);
		//printf("pausing, wait: %d\n", wait);
		//LED_OUT &= ~LED1;
	}
	while (wait) {
		//loop till something else makes wait go to 0

	}
	//if (1) LED_OUT |= LED1;
	//printf("pre-write, pos: %d, val ", sr->pos);
	//pbin(sr->data);
	//printf("\n");
	SR_write(sr, data, bits);
	//printf("post-write, pos: %d, val ", sr->pos);
	//pbin(sr->data);
	//printf("\n");
	return;
}

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

void interrpt(int sig) {
	int x;
	x = SR_read(&output);
	printf("%d", x);
	fflush(NULL);
	wait--;
	signal(sig, interrpt);
}


int main(int argc, const char *argv[])
{
	char *string = "hello world\0";
	int i = 0;
	uint8_t cbrbits = 0;
	srdata cbrdata = 0;
	uint8_t mp;

	SR_init(&output);

	//setup timer
	mytimer.it_interval.tv_sec = 0;
	mytimer.it_interval.tv_usec = 250000;
	mytimer.it_value.tv_sec = 0;
	mytimer.it_value.tv_usec = 250000;

	setitimer(ITIMER_REAL, &mytimer, 0);

	(void) signal(SIGALRM, interrpt);
	printf("starting loop:\n");
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

	return 0;
}

