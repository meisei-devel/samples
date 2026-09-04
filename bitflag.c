#include <stdio.h>
#include <stdint.h>

/* 4バイトフラグ */

#define F_TOKYO		0x00000001
#define F_SAITAMA	0x00000002
#define F_CHIBA		0x00000004
#define F_KANAGAWA	0x00000008
#define F_IBARAKI	0x00000010
#define F_TOCHIGI	0x00000020
#define F_GUNNMA	0x00000040
#define F_YAMANASHI	0x00000080
#define F_SHIZUOKA	0x00000100

int main(int argc, char **argv) {

	uint32_t flag; /* 4バイトフラグ変数 */

	flag = F_TOKYO | F_TOCHIGI; /* 東京と栃木のビットON */

	if(flag & F_TOCHIGI) {
		printf("flag includes F_TOCHIGI\n");
	}

	if(flag & F_TOKYO) {
		printf("flag includes F_TOKYO\n");
	}

	if(flag & F_GUNNMA) {
		printf("flag includes F_GUNNMA\n");
	}

	flag |= F_YAMANASHI; /* 山梨を追加セット */

	if(flag & F_YAMANASHI) {
		printf("flag includes F_YAMANASHI\n");
	}

	return 0;
}
