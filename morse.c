#include "morse.h"
uint8_t lookup[] = {
 MORSE(2, 0x01), //A
 MORSE(4, 0x08), //B
 MORSE(4, 0x0a), //C
 MORSE(3, 0x04), //D
 MORSE(1, 0x00), //E
 MORSE(4, 0x02), //F
 MORSE(3, 0x06), //G
 MORSE(4, 0x00), //H
 MORSE(2, 0x00), //I
 MORSE(4, 0x07), //J
 MORSE(3, 0x05), //K
 MORSE(4, 0x04), //L
 MORSE(2, 0x03), //M
 MORSE(2, 0x02), //N
 MORSE(3, 0x07), //O
 MORSE(4, 0x06), //P
 MORSE(4, 0x0d), //Q
 MORSE(3, 0x02), //R
 MORSE(3, 0x00), //S
 MORSE(1, 0x01), //T
 MORSE(3, 0x01), //U
 MORSE(4, 0x01), //V
 MORSE(3, 0x03), //W
 MORSE(4, 0x09), //X
 MORSE(4, 0x0b), //Y
 MORSE(4, 0x0c), //Z
 MORSE(5, 0x0f), //1
 MORSE(5, 0x07), //2
 MORSE(5, 0x03), //3
 MORSE(5, 0x01), //4
 MORSE(5, 0x00), //5
 MORSE(5, 0x10), //6
 MORSE(5, 0x18), //7
 MORSE(5, 0x1c), //8
 MORSE(5, 0x1e), //9
 MORSE(5, 0x1f)}; //0
#define BAD_ASCII 0x00;


uint8_t convert_ascii(char f) {
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


