#include "kmatrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	KM_DATA a[3][3] = { { 2, 5, 8 }, { 8, 0, 1 }, { 6, 2, 8 } };
	KMatrix *m = KMat_create(3, (KM_DATA **)a);
	printf("m:\n");
	KMat_print(m);
	KMatrix *res = KMat_inverse(m);
	printf("res:\n");
	KMat_print(res);
	return EXIT_SUCCESS;
}
