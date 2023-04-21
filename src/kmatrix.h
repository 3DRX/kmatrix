#ifndef KMATRIX
#define KMATRIX

#include <stddef.h>
#include <stdbool.h>

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

KMatrix *KMat_create(const size_t dim, KM_DATA **value);
KMatrix *KMat_copy(const KMatrix *m);
KMatrix *KMat_zeros(const size_t dim);
KMatrix *KMat_ones(const size_t dim);
KMatrix *KMat_eye(const size_t dim);
void KMat_delete(KMatrix *m);
KMatrix *KMat_T(const KMatrix *m);
void KMat_print(const KMatrix *m);
KMatrix *KMat_dot(const KMatrix *x, const KMatrix *y);
KMatrix *KMat_inverse(const KMatrix *m);
KM_DATA KMat_determinant(const KMatrix *m);
KArray *KMat_toKArr(const KMatrix *m);

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
KArray *KArr_add(const KArray *a, const KArray *b);
KArray *KArr_sub(const KArray *a, const KArray *b);
KArray *KArr_mul(const KArray *a, const KArray *b);
KArray *KArr_div(const KArray *a, const KArray *b);
KArray *KArr_addnum(const KArray *a, const KM_DATA b);
KArray *KArr_subnum(const KArray *a, const KM_DATA b);
KArray *KArr_mulnum(const KArray *a, const KM_DATA b);
KArray *KArr_divnum(const KArray *a, const KM_DATA b);
bool KArr_equal(const KArray *a, const KArray *b);
KArray *KArr_reshape(const KArray *a, const size_t shape0, const size_t shape1);

#endif
