#ifndef _REG_H
#define _REG_H
#include <sys/inttypes.h>

#define     MASK_N(n)  ( ~(~0<<(n)))

struct SR {
    uint8_t pos;
	uint32_t data;
};

#define SR_READABLE(reg) ((reg)->pos > 0)
#define SR_WRITEABLE(reg, bits) (((reg)->pos + bits) <= ((sizeof((reg)->data) * 8)))
//#define SR_WRITEABLE(reg, bits) (((reg)->pos + bits) <= 32)

void SR_write(struct SR *reg, uint32_t val, uint8_t bits);
int SR_read(struct SR *reg);
void SR_init(struct SR *reg);
#endif
