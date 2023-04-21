#include "kmatrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	KArray *a = KArr_create(2, 2, (KM_DATA[]){ 1, 2, 3, 4 });
	KArr_print(a);
	KArray *b = KArr_T(a);
	KArr_print(b);
	KArray *c = KArr_dot(a, b);
	KArr_print(c);
	KMatrix *d = KArr_toKMat(c);
	KMat_print(d);
	return EXIT_SUCCESS;
}
