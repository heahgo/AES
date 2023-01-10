//Shift Rows

#include <stdint.h>
#include <stdio.h>

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

void main() {
	uint8_t m[16] = {
		0x00, 0x01, 0x02, 0x03, 
		0x04, 0x05, 0x06, 0x07, 
		0x08, 0x09, 0x10, 0x11, 
		0x12, 0x13, 0x14, 0x15
	};

	for ( int i = 0; i < 16; i++) {
		printf("%02x ", m[i]);
		if (i % 4 == 3) {
			printf("\n");
		}
	}
	
	shiftRows(m);
	printf("\n");

	for ( int i = 0; i < 16; i++) {
		printf("%02x ", m[i]);
		if (i % 4 == 3) {
			printf("\n");
		}
	}
	
	shiftRowsInv(m);
	printf("\n");

	for ( int i = 0; i < 16; i++) {
		printf("%02x ", m[i]);
		if (i % 4 == 3) {
			printf("\n");
		}
	}



}
