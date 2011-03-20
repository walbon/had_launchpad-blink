#include "morse.h"

unsigned char convert_ascii(char f) {
	if (INR(f,97,122)) {
		//ascii lowercase, make uppercase
		f -= 32;
	}
	if (!(INR(f, 48, 47) || INR(f, 65,90))) {
		return BAD_ASCII;
	} else {
		switch (f) {
			case 'A':
				return L_A;
			case 'B':
				return L_B;
			case 'C':
				return L_C;
			case 'D':
				return L_D;
			case 'E':
				return L_E;
			case 'F':
				return L_F;
			case 'G':
				return L_G;
			case 'H':
				return L_H;
			case 'I':
				return L_I;
			case 'J':
				return L_J;
			case 'K':
				return L_K;
			case 'L':
				return L_L;
			case 'M':
				return L_M;
			case 'N':
				return L_N;
			case 'O':
				return L_O;
			case 'P':
				return L_P;
			case 'Q':
				return L_Q;
			case 'R':
				return L_R;
			case 'S':
				return L_S;
			case 'T':
				return L_T;
			case 'U':
				return L_U;
			case 'V':
				return L_V;
			case 'W':
				return L_W;
			case 'X':
				return L_X;
			case 'Y':
				return L_Y;
			case 'Z':
				return L_Z;
			case '0':
				return L_0;
			case '1':
				return L_1;
			case '2':
				return L_2;
			case '3':
				return L_3;
			case '4':
				return L_4;
			case '5':
				return L_5;
			case '6':
				return L_6;
			case '7':
				return L_7;
			case '8':
				return L_8;
			case '9':
				return L_9;
			default:
				return BAD_ASCII;
		}
		return BAD_ASCII;
	}
}


