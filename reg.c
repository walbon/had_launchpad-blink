/* reg.{c,h} make what is essentially a shift register in code. this allows
 * the writing of n bits at the end, and pulling from the "front" (LSB).
 */
#include "reg.h"

/* SR_write: add n bits to a shift register.
 * inputs:
 *     struct SR *reg : the register to write
 *     int val        : the bits to add to a register
 *     int bits       : the count from LSB of bits that are significant
 */
void SR_write(struct SR *reg, srdata val, uint8_t bits) {
	srdata mask = 0;

	// move the value into the correct position
	val = val << reg->pos;
	/* this mask first opens all bits up to the highest one we want
	 * then undoes those lower than we want vi a the magic of xor
	 * eg if pos = 2 and bits = 2, it does:
	 * mask = 00000000
	 * mask = 00001111
	 * mask = 00001100 */

	mask = MASK_N(reg->pos + bits);
	mask ^= MASK_N(reg->pos);

	// clear the bits in the register that we now wish to set.
	reg->data &= ~mask;
	// make sure our value is 0 except for the bits we defined as important
	val &= mask;
	// set the register
	reg->data |= val;
	// make sure the register's bit position tracker knows about this
	reg->pos += bits;
	return;
}

/* SR_read : take a bit off the "end" of the register. it is the LSB
 * inputs:
 *     struct SR *reg : the registers we are taking from
 * outputs:
 *      int : an integer 1 or 0 depending on the LSB of reg->data
 */
int SR_read(struct SR *reg) {
	int res = reg->data & 1;
	reg->data >>= 1;
	reg->pos--;
	return res;
}

void SR_init(struct SR *reg) {
	reg->pos = 0;
	reg->data = 0;
	return;
}
