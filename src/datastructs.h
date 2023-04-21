#ifndef DATASTRUCTS
#define DATASTRUCTS

#include <stddef.h>

#define KM_DATA long double

typedef struct {
	size_t dim;
	KM_DATA **value;
} KMatrix;

typedef struct {
	size_t shape0;
	size_t shape1;
	KM_DATA *value;
} KArray;

#endif
