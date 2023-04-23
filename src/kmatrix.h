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

// create a KMatrix
KMatrix *KMat_create(const size_t dim, KM_DATA **value);
// deep copy of a KMatrix
KMatrix *KMat_copy(const KMatrix *m);
// create a KMatrix with all elements set to 0
KMatrix *KMat_zeros(const size_t dim);
// create a KMatrix with all elements set to 1
KMatrix *KMat_ones(const size_t dim);
// create a KMatrix with principal diagonal set to 1, and other elements set to 0
KMatrix *KMat_eye(const size_t dim);
// delete a KMatrix
void KMat_delete(KMatrix *m);
// get the transpose of a KMatrix
KMatrix *KMat_T(const KMatrix *m);
// print a KMatrix
void KMat_print(const KMatrix *m);
// dot product of two KMatrix
KMatrix *KMat_dot(const KMatrix *x, const KMatrix *y);
// get the inverse of a KMatrix
KMatrix *KMat_inverse(const KMatrix *m);
// get the determinant of a KMatrix
KM_DATA KMat_determinant(const KMatrix *m);
// get the trace of a KMatrix
KM_DATA KMat_trace(const KMatrix *m);
// get the rank of a KMatrix
size_t KMat_rank(const KMatrix *m);
// get the sum of all elements of a KMatrix
KM_DATA KMat_sum(const KMatrix *m);
// get the mean of all elements of a KMatrix
KM_DATA KMat_mean(const KMatrix *m);
// get the variance of all elements of a KMatrix
KM_DATA KMat_var(const KMatrix *m);
// get the standard deviation of all elements of a KMatrix
KM_DATA KMat_std(const KMatrix *m);
// get the minimum of all elements of a KMatrix
KM_DATA KMat_min(const KMatrix *m);
// get the maximum of all elements of a KMatrix
KM_DATA KMat_max(const KMatrix *m);
// turn a KMatrix into a KArray
KArray *KMat_toKArr(const KMatrix *m);

// create a KArray
KArray *KArr_create(const size_t shape0, const size_t shape1, KM_DATA *value);
// deep copy of a KArray
KArray *KArr_copy(const KArray *a);
// create a KArray with all elements set to 0
KArray *KArr_zeros(const size_t shape0, const size_t shape1);
// create a KArray with all elements set to 1
KArray *KArr_ones(const size_t shape0, const size_t shape1);
// set the value of a KArray at (col, row)
bool KArr_set(const KArray *a, const size_t col, const size_t row,
        KM_DATA value);
// get the value of a KArray at (col, row)
KM_DATA KArr_get(const KArray *a, const size_t col, const size_t row);
// delete a KArray
void KArr_delete(KArray *a);
// get the transpose of a KArray
KArray *KArr_T(const KArray *a);
// print a KArray
void KArr_print(const KArray *a);
// dot product of two KArray
KArray *KArr_dot(const KArray *x, const KArray *y);
// turn a KArray into a KMatrix
KMatrix *KArr_toKMat(const KArray *a);
// add two KArray by element
KArray *KArr_add(const KArray *a, const KArray *b);
// subtract two KArray by element
KArray *KArr_sub(const KArray *a, const KArray *b);
// multiply two KArray by element
KArray *KArr_mul(const KArray *a, const KArray *b);
// divide two KArray by element
KArray *KArr_div(const KArray *a, const KArray *b);
// add all elements of a KArray by a number
KArray *KArr_addnum(const KArray *a, const KM_DATA b);
// subtract all elements of a KArray by a number
KArray *KArr_subnum(const KArray *a, const KM_DATA b);
// multiply all elements of a KArray by a number
KArray *KArr_mulnum(const KArray *a, const KM_DATA b);
// divide all elements of a KArray by a number
KArray *KArr_divnum(const KArray *a, const KM_DATA b);
// if two KArray are equal
bool KArr_equal(const KArray *a, const KArray *b);
// reshape a KArray,
// if the new shape is not compatible with the old shape,
// add 0 to the new KArray when larger, or delete elements when smaller
KArray *KArr_reshape(const KArray *a, const size_t shape0, const size_t shape1);
// get the sum of all elements of a KArray
KM_DATA KArr_sum(const KArray *a);
// get the mean of all elements of a KArray
KM_DATA KArr_mean(const KArray *a);
// get the variance of all elements of a KArray
KM_DATA KArr_var(const KArray *a);
// get the standard deviation of all elements of a KArray
KM_DATA KArr_std(const KArray *a);
// get the minimum of all elements of a KArray
KM_DATA KArr_min(const KArray *a);
// get the maximum of all elements of a KArray
KM_DATA KArr_max(const KArray *a);
// get the rank of a KArray
size_t KArr_rank(const KArray *a);

#endif
