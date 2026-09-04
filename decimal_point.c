#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void) {

	double a = 1.5;

	/* 切り捨て */
	printf("floor=%lf\n", floor(a));

	/* 切り上げ */
	printf("ceil=%lf\n", ceil(a));

	/* 四捨五入 */
	printf("round=%lf\n", round(a));

	return 0;
}
