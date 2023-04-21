#ifndef KARRAY
#define KARRAY

#include "datastructs.h"
#include <stdbool.h>

KArray *KArr_create(const size_t shape0, const size_t shape1, KM_DATA *value);
KArray *KArr_copy(const KArray *a);
KArray *KArr_zeros(const size_t shape0, const size_t shape1);
KArray *KArr_ones(const size_t shape0, const size_t shape1);
bool KArr_set(const KArray *a, const size_t col, const size_t row,
	      KM_DATA value);
KM_DATA KArr_get(const KArray *a, const size_t col, const size_t row);
void KArr_delete(KArray *a);
KArray *KArr_T(const KArray *a);
void KArr_print(const KArray *a);
KArray *KArr_dot(const KArray *x, const KArray *y);
KMatrix *KArr_toKMat(const KArray *a);

#endif
