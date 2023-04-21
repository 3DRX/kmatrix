#include "kmatrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	KM_DATA a[3][3] = { { 6, 2, 3 }, { 4, 5, 6 }, { 7, 10, 9 } };
	KMatrix *m = KMat_create(3, (KM_DATA **)a);
	KMat_print(m);
	KMatrix *res = KMat_inverse(m);
	KMat_print(res);
	return EXIT_SUCCESS;
}
