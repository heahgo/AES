// Mix Column

#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t GF_mul(uint8_t first, uint8_t second) {	//GF_add(a, b) is a ^ b { a Exclusive or b }
	uint8_t x = 0b10000000; //128
	uint8_t result = 0;	// result of GF_mul
	uint8_t div = 0x1b;	//	divider 00011011(2) (x^8 + x^4 + x^3 + x + 1)
	uint8_t tmp;

	for ( int i = 0; i < 8; i++ ) {
		if ( (second & (x >> i)) == (x >> i) ) {	// (7 - i) th Bit check { 2 exp (7 - i) }
			tmp = first;
			for ( int j = 0; j < 7 - i; j++ ) {	// GF_mul first_operator by 2 exp (7 - i)
				if ( (tmp & x) == x ) {	// if first bit is 1
					tmp = tmp << 1;
					tmp = tmp ^ div;
				} else	// if first bit is 0
					tmp = tmp << 1;
			}
			result = result ^ tmp;
		}
	}
	return result;
}

void mixColumn(uint8_t *m) {
	uint8_t mix[16] = {
		2, 3, 1, 1,
		1, 2, 3, 1,
		1, 1, 2, 3,
		3, 1, 1, 2
	};
	uint8_t tmp[16];	//m[16] copy
	memcpy(tmp, m, 16);
	
	//	multiplication matrix 4x4 (mix x m)
	m[0] = GF_mul(mix[0], tmp[0]) ^ GF_mul(mix[1], tmp[4]) ^ GF_mul(mix[2], tmp[8]) ^ GF_mul(mix[3], tmp[12]);	// 0 columns
	m[4] = GF_mul(mix[4], tmp[0]) ^ GF_mul(mix[5], tmp[4]) ^ GF_mul(mix[6], tmp[8]) ^ GF_mul(mix[7], tmp[12]);
	m[8] = GF_mul(mix[8], tmp[0]) ^ GF_mul(mix[9], tmp[4]) ^ GF_mul(mix[10], tmp[8]) ^ GF_mul(mix[11], tmp[12]);
	m[12] = GF_mul(mix[12], tmp[0]) ^ GF_mul(mix[13], tmp[4]) ^ GF_mul(mix[14], tmp[8]) ^ GF_mul(mix[15], tmp[12]);
	
	m[1] = GF_mul(mix[0], tmp[1]) ^ GF_mul(mix[1], tmp[5]) ^ GF_mul(mix[2], tmp[9]) ^ GF_mul(mix[3], tmp[13]);	// 1 columns
	m[5] = GF_mul(mix[4], tmp[1]) ^ GF_mul(mix[5], tmp[5]) ^ GF_mul(mix[6], tmp[9]) ^ GF_mul(mix[7], tmp[13]);
	m[9] = GF_mul(mix[8], tmp[1]) ^ GF_mul(mix[9], tmp[5]) ^ GF_mul(mix[10], tmp[9]) ^ GF_mul(mix[11], tmp[13]);
	m[13] = GF_mul(mix[12], tmp[1]) ^ GF_mul(mix[13], tmp[5]) ^ GF_mul(mix[14], tmp[9]) ^ GF_mul(mix[15], tmp[13]);

	m[2] = GF_mul(mix[0], tmp[2]) ^ GF_mul(mix[1], tmp[6]) ^ GF_mul(mix[2], tmp[10]) ^ GF_mul(mix[3], tmp[14]);	// 2 columns
	m[6] = GF_mul(mix[4], tmp[2]) ^ GF_mul(mix[5], tmp[6]) ^ GF_mul(mix[6], tmp[10]) ^ GF_mul(mix[7], tmp[14]);
	m[10] = GF_mul(mix[8], tmp[2]) ^ GF_mul(mix[9], tmp[6]) ^ GF_mul(mix[10], tmp[10]) ^ GF_mul(mix[11], tmp[14]);
	m[14] = GF_mul(mix[12], tmp[2]) ^ GF_mul(mix[13], tmp[6]) ^ GF_mul(mix[14], tmp[10]) ^ GF_mul(mix[15], tmp[14]);

	m[3] = GF_mul(mix[0], tmp[3]) ^ GF_mul(mix[1], tmp[7]) ^ GF_mul(mix[2], tmp[11]) ^ GF_mul(mix[3], tmp[15]);	// 3 columns
	m[7] = GF_mul(mix[4], tmp[3]) ^ GF_mul(mix[5], tmp[7]) ^ GF_mul(mix[6], tmp[11]) ^ GF_mul(mix[7], tmp[15]);
	m[11] = GF_mul(mix[8], tmp[3]) ^ GF_mul(mix[9], tmp[7]) ^ GF_mul(mix[10], tmp[11]) ^ GF_mul(mix[11], tmp[15]);
	m[15] = GF_mul(mix[12], tmp[3]) ^ GF_mul(mix[13], tmp[7]) ^ GF_mul(mix[14], tmp[11]) ^ GF_mul(mix[15], tmp[15]);
}

void mixColumnInv(uint8_t *m) {
	uint8_t mixInv[16] = {
		14, 11, 13, 9,
		9, 14, 11, 13,
		13, 9, 14, 11,
		11, 13, 9, 14
	};

	uint8_t tmp[16];	//m[16] copy
	memcpy(tmp, m, 16);
	
	//	multiplication matrix 4x4 (mix x m)
	m[0] = GF_mul(mixInv[0], tmp[0]) ^ GF_mul(mixInv[1], tmp[4]) ^ GF_mul(mixInv[2], tmp[8]) ^ GF_mul(mixInv[3], tmp[12]);	// 0 columns
	m[4] = GF_mul(mixInv[4], tmp[0]) ^ GF_mul(mixInv[5], tmp[4]) ^ GF_mul(mixInv[6], tmp[8]) ^ GF_mul(mixInv[7], tmp[12]);
	m[8] = GF_mul(mixInv[8], tmp[0]) ^ GF_mul(mixInv[9], tmp[4]) ^ GF_mul(mixInv[10], tmp[8]) ^ GF_mul(mixInv[11], tmp[12]);
	m[12] = GF_mul(mixInv[12], tmp[0]) ^ GF_mul(mixInv[13], tmp[4]) ^ GF_mul(mixInv[14], tmp[8]) ^ GF_mul(mixInv[15], tmp[12]);
	
	m[1] = GF_mul(mixInv[0], tmp[1]) ^ GF_mul(mixInv[1], tmp[5]) ^ GF_mul(mixInv[2], tmp[9]) ^ GF_mul(mixInv[3], tmp[13]);	// 1 columns
	m[5] = GF_mul(mixInv[4], tmp[1]) ^ GF_mul(mixInv[5], tmp[5]) ^ GF_mul(mixInv[6], tmp[9]) ^ GF_mul(mixInv[7], tmp[13]);
	m[9] = GF_mul(mixInv[8], tmp[1]) ^ GF_mul(mixInv[9], tmp[5]) ^ GF_mul(mixInv[10], tmp[9]) ^ GF_mul(mixInv[11], tmp[13]);
	m[13] = GF_mul(mixInv[12], tmp[1]) ^ GF_mul(mixInv[13], tmp[5]) ^ GF_mul(mixInv[14], tmp[9]) ^ GF_mul(mixInv[15], tmp[13]);

	m[2] = GF_mul(mixInv[0], tmp[2]) ^ GF_mul(mixInv[1], tmp[6]) ^ GF_mul(mixInv[2], tmp[10]) ^ GF_mul(mixInv[3], tmp[14]);	// 2 columns
	m[6] = GF_mul(mixInv[4], tmp[2]) ^ GF_mul(mixInv[5], tmp[6]) ^ GF_mul(mixInv[6], tmp[10]) ^ GF_mul(mixInv[7], tmp[14]);
	m[10] = GF_mul(mixInv[8], tmp[2]) ^ GF_mul(mixInv[9], tmp[6]) ^ GF_mul(mixInv[10], tmp[10]) ^ GF_mul(mixInv[11], tmp[14]);
	m[14] = GF_mul(mixInv[12], tmp[2]) ^ GF_mul(mixInv[13], tmp[6]) ^ GF_mul(mixInv[14], tmp[10]) ^ GF_mul(mixInv[15], tmp[14]);

	m[3] = GF_mul(mixInv[0], tmp[3]) ^ GF_mul(mixInv[1], tmp[7]) ^ GF_mul(mixInv[2], tmp[11]) ^ GF_mul(mixInv[3], tmp[15]);	// 3 columns
	m[7] = GF_mul(mixInv[4], tmp[3]) ^ GF_mul(mixInv[5], tmp[7]) ^ GF_mul(mixInv[6], tmp[11]) ^ GF_mul(mixInv[7], tmp[15]);
	m[11] = GF_mul(mixInv[8], tmp[3]) ^ GF_mul(mixInv[9], tmp[7]) ^ GF_mul(mixInv[10], tmp[11]) ^ GF_mul(mixInv[11], tmp[15]);
	m[15] = GF_mul(mixInv[12], tmp[3]) ^ GF_mul(mixInv[13], tmp[7]) ^ GF_mul(mixInv[14], tmp[11]) ^ GF_mul(mixInv[15], tmp[15]);
}

void main() {	
	uint8_t m[16] = {
		0x93, 0x6d, 0xe1, 0x10,
		0x33, 0x80, 0x73, 0xde,
		0xfc, 0x76, 0xc5, 0x5b,
		0x82, 0xd4, 0x13, 0x93
	};

	for (int i = 0; i < 16; i++) {
		printf("%02x ", m[i]);
		if (i % 4 == 3)
			printf("\n");
	}

	mixColumn(m);
	printf("\n");

	for (int i = 0; i < 16; i++) {
		printf("%02x ", m[i]);
		if (i % 4 == 3)
			printf("\n");
	}

	mixColumnInv(m);
	printf("\n");

	for (int i = 0; i < 16; i++) {
		printf("%02x ", m[i]);
		if (i % 4 == 3)
			printf("\n");
	}

}

