#include "karray.h"
#include "datastructs.h"
#include "kmatrix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

KArray *KArr_create(const size_t shape0, const size_t shape1, KM_DATA *value)
{
	KArray *res = (KArray *)malloc(sizeof(KArray));
	res->shape0 = shape0;
	res->shape1 = shape1;
	res->value = (KM_DATA *)malloc(sizeof(KM_DATA) * shape0 * shape1);
	for (int i = 0; i < shape0 * shape1; i++) {
		res->value[i] = value[i];
	}
	return res;
}

KArray *KArr_zeros(const size_t shape0, const size_t shape1)
{
	KArray *res = (KArray *)malloc(sizeof(KArray));
	res->shape0 = shape0;
	res->shape1 = shape1;
	res->value = (KM_DATA *)malloc(sizeof(KM_DATA) * shape0 * shape1);
	for (int i = 0; i < shape0 * shape1; i++) {
		res->value[i] = 0;
	}
	return res;
}

KArray *Krr_ones(const size_t shape0, const size_t shape1)
{
	KArray *res = (KArray *)malloc(sizeof(KArray));
	res->shape0 = shape0;
	res->shape1 = shape1;
	res->value = (KM_DATA *)malloc(sizeof(KM_DATA) * shape0 * shape1);
	for (int i = 0; i < shape0 * shape1; i++) {
		res->value[i] = 1;
	}
	return res;
}

KArray *KArr_copy(const KArray *a)
{
	KArray *res = (KArray *)malloc(sizeof(KArray));
	res->shape0 = a->shape0;
	res->shape1 = a->shape1;
	res->value = (KM_DATA *)malloc(sizeof(KM_DATA) * a->shape0 * a->shape1);
	for (int i = 0; i < a->shape0 * a->shape1; i++) {
		res->value[i] = a->value[i];
	}
	return res;
}

void KArr_delete(KArray *a)
{
	free(a->value);
	free(a);
}

KArray *KArr_T(const KArray *a)
{
	KArray *res = (KArray *)malloc(sizeof(KArray));
	res->shape0 = a->shape1;
	res->shape1 = a->shape0;
	res->value = (KM_DATA *)malloc(sizeof(KM_DATA) * a->shape0 * a->shape1);
	for (int col = 0; col < res->shape0; col++) {
		for (int row = 0; row < res->shape1; row++) {
			KArr_set(res, col, row, KArr_get(a, row, col));
		}
	}
	return res;
}

bool KArr_set(const KArray *a, const size_t col, const size_t row,
	      long double value)
{
	if (col >= 0 && col < a->shape0 && row >= 0 && row <= a->shape1) {
		a->value[col * a->shape1 + row] = value;
		return true;
	} else {
		fprintf(stderr, "ERROR (KArr_set): index out of range\n");
		return false;
	}
}

KM_DATA KArr_get(const KArray *a, const size_t col, const size_t row)
{
	if (col >= 0 && col < a->shape0 && row >= 0 && row <= a->shape1) {
		return a->value[col * a->shape1 + row];
	} else {
		fprintf(stderr, "ERROR (KArr_get): index out of range\n");
		return 0;
	}
}

void KArr_print(const KArray *a)
{
	printf("[\n");
	for (int col = 0; col < a->shape0; col++) {
		printf("\t");
		for (int row = 0; row < a->shape1; row++) {
			if (row == 0) {
				printf("%Lf", KArr_get(a, col, row));
			} else {
				printf(" %Lf", KArr_get(a, col, row));
			}
		}
		printf("\n");
	}
	printf("]\n");
}

KArray *KArr_dot(const KArray *a, const KArray *b)
{
	if (a->shape1 != b->shape0) {
		fprintf(stderr, "ERROR (KArr_dot): shape mismatch\n");
		return NULL;
	}
	KArray *res = KArr_zeros(a->shape0, b->shape1);
	for (int col = 0; col < res->shape0; col++) {
		for (int row = 0; row < res->shape1; row++) {
			KM_DATA sum = 0;
			for (int i = 0; i < a->shape1; i++) {
				sum += KArr_get(a, col, i) *
				       KArr_get(b, i, row);
			}
			KArr_set(res, col, row, sum);
		}
	}
	return res;
}

KMatrix *KArr_toKMat(const KArray *a)
{
	if (a->shape1 != a->shape0) {
		fprintf(stderr, "ERROR (toMatrix): not square\n");
		return NULL;
	}
	KMatrix *res = KMat_zeros(a->shape0);
	for (int col = 0; col < a->shape0; col++) {
		for (int row = 0; row < a->shape1; row++) {
			res->value[col][row] = KArr_get(a, col, row);
		}
	}
	return res;
}

KArray *KArr_add(const KArray *a, const KArray *b)
{
	if (a->shape0 != b->shape0 || a->shape1 != b->shape1) {
		fprintf(stderr, "ERROR (KArr_add): shape mismatch\n");
		return NULL;
	}
	KArray *res = KArr_zeros(a->shape0, a->shape1);
	for (int col = 0; col < res->shape0; col++) {
		for (int row = 0; row < res->shape1; row++) {
			KArr_set(res, col, row,
				 KArr_get(a, col, row) + KArr_get(b, col, row));
		}
	}
	return res;
}

KArray *KArr_sub(const KArray *a, const KArray *b)
{
	if (a->shape0 != b->shape0 || a->shape1 != b->shape1) {
		fprintf(stderr, "ERROR (KArr_sub): shape mismatch\n");
		return NULL;
	}
	KArray *res = KArr_zeros(a->shape0, a->shape1);
	for (int col = 0; col < res->shape0; col++) {
		for (int row = 0; row < res->shape1; row++) {
			KArr_set(res, col, row,
				 KArr_get(a, col, row) - KArr_get(b, col, row));
		}
	}
	return res;
}

KArray *KArr_mul(const KArray *a, const KArray *b)
{
	if (a->shape0 != b->shape0 || a->shape1 != b->shape1) {
		fprintf(stderr, "ERROR (KArr_mul): shape mismatch\n");
		return NULL;
	}
	KArray *res = KArr_zeros(a->shape0, a->shape1);
	for (int col = 0; col < res->shape0; col++) {
		for (int row = 0; row < res->shape1; row++) {
			KArr_set(res, col, row,
				 KArr_get(a, col, row) * KArr_get(b, col, row));
		}
	}
	return res;
}

KArray *KArr_div(const KArray *a, const KArray *b)
{
	if (a->shape0 != b->shape0 || a->shape1 != b->shape1) {
		fprintf(stderr, "ERROR (KArr_div): shape mismatch\n");
		return NULL;
	}
	KArray *res = KArr_zeros(a->shape0, a->shape1);
	for (int col = 0; col < res->shape0; col++) {
		for (int row = 0; row < res->shape1; row++) {
			KArr_set(res, col, row,
				 KArr_get(a, col, row) / KArr_get(b, col, row));
		}
	}
	return res;
}

KArray *KArr_addnum(const KArray *a, const KM_DATA b)
{
	KArray *res = KArr_zeros(a->shape0, a->shape1);
	for (int col = 0; col < res->shape0; col++) {
		for (int row = 0; row < res->shape1; row++) {
			KArr_set(res, col, row, KArr_get(a, col, row) + b);
		}
	}
	return res;
}

KArray *KArr_subnum(const KArray *a, const KM_DATA b)
{
	KArray *res = KArr_zeros(a->shape0, a->shape1);
	for (int col = 0; col < res->shape0; col++) {
		for (int row = 0; row < res->shape1; row++) {
			KArr_set(res, col, row, KArr_get(a, col, row) - b);
		}
	}
	return res;
}

KArray *KArr_mulnum(const KArray *a, const KM_DATA b)
{
	KArray *res = KArr_zeros(a->shape0, a->shape1);
	for (int col = 0; col < res->shape0; col++) {
		for (int row = 0; row < res->shape1; row++) {
			KArr_set(res, col, row, KArr_get(a, col, row) * b);
		}
	}
	return res;
}

KArray *KArr_divnum(const KArray *a, const KM_DATA b)
{
	KArray *res = KArr_zeros(a->shape0, a->shape1);
	for (int col = 0; col < res->shape0; col++) {
		for (int row = 0; row < res->shape1; row++) {
			KArr_set(res, col, row, KArr_get(a, col, row) / b);
		}
	}
	return res;
}

bool KArr_equal(const KArray *a, const KArray *b)
{
	if (a->shape0 != b->shape0 || a->shape1 != b->shape1) {
		fprintf(stderr, "ERROR (KArr_equal): shape mismatch\n");
		return false;
	}
	for (int col = 0; col < a->shape0; col++) {
		for (int row = 0; row < a->shape1; row++) {
			if (KArr_get(a, col, row) != KArr_get(b, col, row)) {
				return false;
			}
		}
	}
	return true;
}

KArray *KArr_reshape(KArray *a, const size_t shape0, const size_t shape1)
{
	KArray *newArr = KArr_zeros(shape0, shape1);
	for (int i = 0; i < shape0 * shape1; i++) {
		if (i < a->shape0 * a->shape1) {
			newArr->value[i] = a->value[i];
		} else {
			newArr->value[i] = 0;
		}
	}
	return newArr;
}
