struct SR {
	unsigned char pos;
	unsigned int data;
};

#define SR_READABLE(reg) ((reg)->pos > 0)
#define SR_WRITABLE(reg, bits) (((reg)->pos + bits) <= ((sizeof((reg)->data) * 8)))

void SR_write(struct SR *reg, int val, int bits);
int SR_read(struct SR *reg);
