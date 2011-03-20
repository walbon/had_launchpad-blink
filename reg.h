#ifndef _REG_H
#define _REG_H
struct SR {
	unsigned char pos;
	unsigned long long data;
};

#define SR_READABLE(reg) ((reg)->pos > 0)
#define SR_WRITEABLE(reg, bits) (((reg)->pos + bits) <= ((sizeof((reg)->data) * 8)))

void SR_write(struct SR *reg, int val, int bits);
int SR_read(struct SR *reg);
void SR_init(struct SR *reg);
#endif
