#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t SBox[256] = {
	//  0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
		0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,	// 0
		0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, // 1
		0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,	// 2
		0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,	// 3
		0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,	// 4
		0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,	// 5
		0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,	// 6
		0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,	// 7
		0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,	// 8
		0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,	// 9
		0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,	// a
		0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,	// b
		0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,	// c
		0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,	// d
		0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,	// e
		0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16	// f
	};

uint8_t SBoxInv[256] = {
	//  0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
		0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,	// 0
	    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, // 1
		0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, // 2
		0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, // 3
		0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, // 4
	    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, // 5
	    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, // 6
	    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, // 7
	    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, // 8
	    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, // 9
	    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, // a
	    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, // b
	    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, // c
	    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, // d
	    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, // e
	    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d  // f
	};

void subBytes(uint8_t *m) {
	for ( int i = 0; i < 16; i++ )
		m[i] = SBox[m[i]];
}

void subBytesInv(uint8_t *m) {
	for ( int i = 0; i < 16; i++ )
		m[i] = SBoxInv[m[i]];
}

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

void shiftRows(uint8_t *m) {
	uint8_t tmp1, tmp2;
	
	tmp1 = m[4];	// 1 rows, 1 shift left
	m[4] = m[5];
	m[5] = m[6];
	m[6] = m[7];
	m[7] = tmp1;

	tmp1 = m[8];	// 2 rows, 2 shift left
	tmp2 = m[9];
	m[8] = m[10];
	m[9] = m[11];
	m[10] = tmp1;
	m[11] = tmp2;

	tmp1 = m[12];	// 3 rows, 3 shift left
	m[12] = m[13];
	m[13] = m[14];
	m[14] = m[15];
	m[15] = tmp1;
}

void shiftRowsInv(uint8_t *m) {
	uint8_t tmp1, tmp2;

	tmp1 = m[4];	// 1 rows, 1 shift right
	m[4] = m[7];
	m[7] = m[6];
	m[6] = m[5];
	m[5] = tmp1;

	tmp1 = m[8];	// 2 rows, 2 shift right 
	tmp2 = m[9];
	m[8] = m[10];
	m[9] = m[11];
	m[10] = tmp1;
	m[11] = tmp2;
	
	tmp1 = m[12];	// 3 rows, 3 shift right
	m[12] = m[15];
	m[15] = m[14];
	m[14] = m[13];
	m[13] = tmp1;
}

void keySchdule(uint8_t *key) {
	// Round Constant
	uint8_t rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

	for ( int i = 0; i < 10; i++ ) {
		key[0 + (i + 1) * 16] = key[13 + i * 16];	// shift
		key[1 + (i + 1) * 16] = key[14 + i * 16];
		key[2 + (i + 1) * 16] = key[15 + i * 16];
		key[3 + (i + 1) * 16] = key[12 + i * 16];

		key[0 + (i + 1) * 16] = SBox[key[0 + (i + 1) * 16]];	//SBox
		key[1 + (i + 1) * 16] = SBox[key[1 + (i + 1) * 16]];
		key[2 + (i + 1) * 16] = SBox[key[2 + (i + 1) * 16]];
		key[3 + (i + 1) * 16] = SBox[key[3 + (i + 1) * 16]];

		key[0 + (i + 1) * 16] = key[0 + (i + 1) * 16] ^ rcon[i];	//rcon xor

		key[0 + (i + 1) * 16] = key[0 + (i + 1) * 16] ^ key[0 + i * 16];	//xor
		key[1 + (i + 1) * 16] = key[1 + (i + 1) * 16] ^ key[1 + i * 16];
		key[2 + (i + 1) * 16] = key[2 + (i + 1) * 16] ^ key[2 + i * 16];
		key[3 + (i + 1) * 16] = key[3 + (i + 1) * 16] ^ key[3 + i * 16];

		for ( int j = 0; j < 3; j++ ) {
		key[4 + (j * 4) + (i + 1) * 16] = key[0 + (j * 4) + (i + 1) * 16] ^ key[4 + (j * 4) + i * 16];
		key[5 + (j * 4) + (i + 1) * 16] = key[1 + (j * 4) + (i + 1) * 16] ^ key[5 + (j * 4) + i * 16];
		key[6 + (j * 4) + (i + 1) * 16] = key[2 + (j * 4) + (i + 1) * 16] ^ key[6 + (j * 4) + i * 16];
		key[7 + (j * 4) + (i + 1) * 16] = key[3 + (j * 4) + (i + 1) * 16] ^ key[7 + (j * 4) + i * 16];
		}
	}
}

void addRoundKey(uint8_t *m, uint8_t *key, int round) {
	for ( int i = 0; i < 16; i++ ) {
		m[i] = m[i] ^ key[i + round * 16];
	}
}

void encryption(uint8_t *m, uint8_t *key) {
	addRoundKey(m, key, 0);
	for ( int i = 1; i <= 9; i++ ) {
		subBytes(m);
		shiftRows(m);
		mixColumn(m);
		addRoundKey(m, key, i);
	}	
	subBytes(m);
	shiftRows(m);
	addRoundKey(m, key, 10);
}

void decryption(uint8_t *m, uint8_t *key) {
	addRoundKey(m, key, 10);
	for ( int i = 9; i > 0; i-- ) {
		shiftRowsInv(m);
		subBytesInv(m);
		addRoundKey(m, key, i);
		mixColumnInv(m);
	}
	shiftRowsInv(m);
	subBytesInv(m);
	addRoundKey(m, key, 0);
}

void printMsg(uint8_t *m) {
	for ( int i = 0; i < 16; i++ ) {
		printf("%02x ", m[i]);
		if (i % 4 == 3)
			printf("\n");
	}
	printf("\n");
}

void main() {
	uint8_t m[16] = {
		0x00, 0x01, 0x02, 0x03,
		0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x10, 0x11,
		0x12, 0x13, 0x14, 0x15
	};
	uint8_t key[16 * 11] = {
		0x54, 0x68, 0x61, 0x74,
		0x73, 0x20, 0x6d, 0x79,
		0x20, 0x4b, 0x75, 0x6e,
		0x67, 0x20, 0x46, 0x75,
		0x00,
	};
	keySchdule(key);
	printMsg(m);
	encryption(m, key);
	printMsg(m);
	decryption(m, key);
	printMsg(m);
}
