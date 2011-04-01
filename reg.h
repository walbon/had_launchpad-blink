#ifndef _REG_H
#define _REG_H
//#include <sys/inttypes.h>
#include <stdint.h>

#define     MASK_N(n)  ( ~(~0<<(n)))

typedef uint16_t srdata ;

struct SR {
    uint8_t pos;
	srdata data;
};

#define SR_READABLE(reg) ((reg)->pos > 0)
#define SR_WRITEABLE(reg, bits) (((reg)->pos + bits) <= ((sizeof((reg)->data) * 8)))
//#define SR_WRITEABLE(reg, bits) (((reg)->pos + bits) <= 16)

void SR_write(struct SR *reg, srdata val, uint8_t bits);
int SR_read(struct SR *reg);
void SR_init(struct SR *reg);
#endif
