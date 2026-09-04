/* stdint.h/uint64_tを使ったビットフラグ */
#include <stdio.h>
#include <stdint.h>

#define F_BIT01_1 0x0000000000000001
#define F_BIT01_2 0x0000000000000002
#define F_BIT01_4 0x0000000000000004
#define F_BIT01_8 0x0000000000000008

#define F_BIT16_1 0x1000000000000000
#define F_BIT16_2 0x2000000000000000
#define F_BIT16_4 0x4000000000000000
#define F_BIT16_8 0x8000000000000000

int main(void) {
	uint64_t bit;

	bit = F_BIT01_1 | F_BIT16_8;

	printf("bit = %016lX\n", bit);

	if(bit & F_BIT01_1) {
		printf("F_BIT01_1 IS ON\n");
	}

	if(bit & F_BIT16_8) {
		printf("F_BIT16_8 IS ON\n");
	}

	if(!(bit & F_BIT01_8)) {
		printf("F_BIT01_8 IS OFF\n");
	}

	/* 特定のビットをONにする */

	bit |= F_BIT01_8;

	printf("bit = %016lX\n", bit);

	if(bit & F_BIT01_8) {
		printf("F_BIT01_8 IS ON\n");
	}

	/* 特定のビットをOFFにする */

	bit &= ~(F_BIT01_8);

	printf("bit = %016lX\n", bit);

	if(!(bit & F_BIT01_8)) {
		printf("F_BIT01_8 IS OFF\n");
	}

	return 0;
}
