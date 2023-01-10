//Galois Field Calculator

#include <stdint.h>
#include <stdio.h> 

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

void main(int argc, char *argv[1]) {
	if ( argc !=  3 ) {
		printf("usage : <first operator> <second operator>\n");
		return;
	}
	printf("%s * %s = %d\n", argv[1], argv[2], GF_mul(atoi(argv[1]), atoi(argv[2])));
}
