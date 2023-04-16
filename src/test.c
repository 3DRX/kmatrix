#include "kmatrix.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
	KM_DATA a[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
	KMatrix *m = KMat_create(3, &a[0][0]);
	KMat_print(m);
	KM_DATA b[3][3] = { { 1, 1, 2 }, { 3, 3, 4 }, { 8, 8, 9 } };
	KMatrix *n = KMat_create(3, &b[0][0]);
	KMat_print(n);
	KMatrix *res = KMat_dot(m, n);
	KMat_print(res);
	KMat_delete(m);
	KMat_delete(n);
	KMat_delete(res);
	return EXIT_SUCCESS;
}
