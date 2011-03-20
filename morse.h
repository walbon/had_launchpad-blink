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
#define M_VAL(val)  (val & 0x1f)
#define INR(v, a, b) ((v >= a) && (v <=b))

unsigned char convert_ascii(char f);
#endif
