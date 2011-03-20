#ifndef _MORSE_H
#define _MORSE_H
// unit is just a base lenght of time -- setting up a
// sane default just in case we don't -D it later

// All definitions based on the wikipedia Morse Code article and its definition of
// International morse code (in the fancy picture)

// Now define dot, this will be the new base
#define DOT 1
#define	DASH 3
#define OFF DOT
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

#define L_A MORSE(2, 0x01);
#define L_B MORSE(4, 0x08);
#define L_C MORSE(4, 0x0a);
#define L_D MORSE(3, 0x04);
#define L_E MORSE(1, 0x00);
#define L_F MORSE(4, 0x02);
#define L_G MORSE(3, 0x06);
#define L_H MORSE(4, 0x00);
#define L_I MORSE(2, 0x00);
#define L_J MORSE(4, 0x07);
#define L_K MORSE(3, 0x05);
#define L_L MORSE(4, 0x04);
#define L_M MORSE(2, 0x03);
#define L_N MORSE(2, 0x02);
#define L_O MORSE(3, 0x07);
#define L_P MORSE(4, 0x06);
#define L_Q MORSE(4, 0x0d);
#define L_R MORSE(3, 0x02);
#define L_S MORSE(3, 0x00);
#define L_T MORSE(1, 0x01);
#define L_U MORSE(3, 0x01);
#define L_V MORSE(4, 0x01);
#define L_W MORSE(3, 0x03);
#define L_X MORSE(4, 0x09);
#define L_Y MORSE(4, 0x0b);
#define L_Z MORSE(4, 0x0c);
#define L_1 MORSE(5, 0x0f);
#define L_2 MORSE(5, 0x07);
#define L_3 MORSE(5, 0x03);
#define L_4 MORSE(5, 0x01);
#define L_5 MORSE(5, 0x00);
#define L_6 MORSE(5, 0x10);
#define L_7 MORSE(5, 0x18);
#define L_8 MORSE(5, 0x1c);
#define L_9 MORSE(5, 0x1e);
#define L_0 MORSE(5, 0x1f);
#define BAD_ASCII 0x00;

unsigned char convert_ascii(char f);
#endif
