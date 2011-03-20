#ifndef _MORSE_H
#define _MORSE_H
// unit is just a base lenght of time -- setting up a
// sane default just in case we don't -D it later
#ifndef UNIT
#define UNIT_TIME 1000
#endif

// All definitions based on the wikipedia Morse Code article and its definition of
// International morse code (in the fancy picture)

// Now define dot, this will be the new base
#define DOT = 1
#define	DASH = 3
#define OFF = DOT
#define	LS (DOT * 3) //letter spacing
#define WS (DOT * 7) //word spacing

/* Letters (and numbers)
 * Encoded like so:
 * highest order 3 bits: a count of letter size.
 * lower 5 bits:  0 = dot, 1 = dash, only n LSB count (where N is defined by
 *                the count bits)
 */
#define MORSE(count, val) ((count << 5) + val)

#define M_SIZE(val) (val >> 5)
#define M_VAL(val)  (val & 0xe0)
#define INR(v, a, b) ((v >= a) && (v <=b))

const unsigned char L_A = MORSE(2, 0x01);
const unsigned char L_B = MORSE(4, 0x08);
const unsigned char L_C = MORSE(4, 0x0a);
const unsigned char L_D = MORSE(3, 0x04);
const unsigned char L_E = MORSE(1, 0x00);
const unsigned char L_F = MORSE(4, 0x02);
const unsigned char L_G = MORSE(3, 0x06);
const unsigned char L_H = MORSE(4, 0x00);
const unsigned char L_I = MORSE(2, 0x00);
const unsigned char L_J = MORSE(4, 0x07);
const unsigned char L_K = MORSE(3, 0x05);
const unsigned char L_L = MORSE(4, 0x04);
const unsigned char L_M = MORSE(2, 0x03);
const unsigned char L_N = MORSE(2, 0x02);
const unsigned char L_O = MORSE(3, 0x07);
const unsigned char L_P = MORSE(4, 0x06);
const unsigned char L_Q = MORSE(4, 0x0d);
const unsigned char L_R = MORSE(3, 0x02);
const unsigned char L_S = MORSE(3, 0x00);
const unsigned char L_T = MORSE(1, 0x01);
const unsigned char L_U = MORSE(3, 0x01);
const unsigned char L_V = MORSE(4, 0x01);
const unsigned char L_W = MORSE(3, 0x03);
const unsigned char L_X = MORSE(4, 0x09);
const unsigned char L_Y = MORSE(4, 0x0b);
const unsigned char L_Z = MORSE(4, 0x0c);
const unsigned char L_1 = MORSE(5, 0x0f);
const unsigned char L_2 = MORSE(5, 0x07);
const unsigned char L_3 = MORSE(5, 0x03);
const unsigned char L_4 = MORSE(5, 0x01);
const unsigned char L_5 = MORSE(5, 0x00);
const unsigned char L_6 = MORSE(5, 0x10);
const unsigned char L_7 = MORSE(5, 0x18);
const unsigned char L_8 = MORSE(5, 0x1c);
const unsigned char L_9 = MORSE(5, 0x1e);
const unsigned char L_0 = MORSE(5, 0x1f);
const unsigned char BAD_ASCII = 0x00;

const unsigned char convert_ascii(char f);
#endif
