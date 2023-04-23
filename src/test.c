#include "kmatrix.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	KArray *a = KArr_create(3, 3, (KM_DATA[]){ 1, 1, 2, 2, 2, 4, 5, 2, 7 });
	KArr_print(a);
	size_t res = KArr_rank(a);
	printf("Rank: %zu\n", res);
	KArr_print(a);
	return EXIT_SUCCESS;
}
