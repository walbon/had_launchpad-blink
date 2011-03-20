#include "morse.h"
unsigned char lookup[] = {
 MORSE(2, 0x01),
 MORSE(4, 0x08),
 MORSE(4, 0x0a),
 MORSE(3, 0x04),
 MORSE(1, 0x00),
 MORSE(4, 0x02),
 MORSE(3, 0x06),
 MORSE(4, 0x00),
 MORSE(2, 0x00),
 MORSE(4, 0x07),
 MORSE(3, 0x05),
 MORSE(4, 0x04),
 MORSE(2, 0x03),
 MORSE(2, 0x02),
 MORSE(3, 0x07),
 MORSE(4, 0x06),
 MORSE(4, 0x0d),
 MORSE(3, 0x02),
 MORSE(3, 0x00),
 MORSE(1, 0x01),
 MORSE(3, 0x01),
 MORSE(4, 0x01),
 MORSE(3, 0x03),
 MORSE(4, 0x09),
 MORSE(4, 0x0b),
 MORSE(4, 0x0c),
 MORSE(5, 0x0f),
 MORSE(5, 0x07),
 MORSE(5, 0x03),
 MORSE(5, 0x01),
 MORSE(5, 0x00),
 MORSE(5, 0x10),
 MORSE(5, 0x18),
 MORSE(5, 0x1c),
 MORSE(5, 0x1e),
 MORSE(5, 0x1f)};
#define BAD_ASCII 0x00;


unsigned char convert_ascii(char f) {
	//ascii lowercase, make uppercase
	if (INR(f,97,122)) {
		f -= 32;
	}
	//ASCII char
	if (INR(f, 65,90)) {
		return lookup[f-65];
	//Numeric
	} else if (INR(f, 48, 57)) {
		// 48-26 = 22
		return lookup[f-22];
	} else {
		return BAD_ASCII;
	}
}


