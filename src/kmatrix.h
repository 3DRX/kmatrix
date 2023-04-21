#ifndef KMATRIX
#define KMATRIX

#include "datastructs.h"

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
KArray *toKArray(const KMatrix *m);

#endif
