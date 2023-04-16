#include "kmatrix.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

KMatrix *KMat_create(const size_t dim, const KM_DATA *value)
{
	KMatrix *res = (KMatrix *)malloc(sizeof(KMatrix));
	res->dim = dim;
	res->value = (KM_DATA **)malloc(sizeof(KM_DATA *) * dim);
	for (int i = 0; i < dim; i++) {
		res->value[i] = (KM_DATA *)malloc(sizeof(KM_DATA) * dim);
		for (int j = 0; j < dim; j++) {
			res->value[i][j] = value[i * dim + j];
		}
	}
	return res;
}

KMatrix *KMat_zeros(const size_t dim)
{
	KMatrix *res = (KMatrix *)malloc(sizeof(KMatrix));
	res->dim = dim;
	res->value = (KM_DATA **)malloc(sizeof(KM_DATA *) * dim);
	for (int i = 0; i < dim; i++) {
		res->value[i] = (KM_DATA *)malloc(sizeof(KM_DATA) * dim);
		for (int j = 0; j < dim; j++) {
			res->value[i][j] = 0;
		}
	}
	return res;
}

KMatrix *KMat_ones(const size_t dim)
{
	KMatrix *res = (KMatrix *)malloc(sizeof(KMatrix));
	res->dim = dim;
	res->value = (KM_DATA **)malloc(sizeof(KM_DATA *) * dim);
	for (int i = 0; i < dim; i++) {
		res->value[i] = (KM_DATA *)malloc(sizeof(KM_DATA) * dim);
		for (int j = 0; j < dim; j++) {
			res->value[i][j] = 1;
		}
	}
	return res;
}

KMatrix *KMat_eye(const size_t dim)
{
	KMatrix *res = (KMatrix *)malloc(sizeof(KMatrix));
	res->dim = dim;
	res->value = (KM_DATA **)malloc(sizeof(KM_DATA *) * dim);
	for (int i = 0; i < dim; i++) {
		res->value[i] = (KM_DATA *)malloc(sizeof(KM_DATA) * dim);
		for (int j = 0; j < dim; j++) {
			if (i == j) {
				res->value[i][j] = 1;
			} else {
				res->value[i][j] = 0;
			}
		}
	}
	return res;
}

KMatrix *KMat_T(const KMatrix *m)
{
	KMatrix *res = KMat_zeros(m->dim);
	for (int col = 0; col < m->dim; col++) {
		for (int row = 0; row < m->dim; row++) {
			res->value[col][row] = m->value[row][col];
		}
	}
	return res;
}

void KMat_delete(KMatrix *m)
{
	for (int i = 0; i < m->dim; i++) {
		free(m->value[i]);
	}
	free(m->value);
	free(m);
}

void KMat_print(const KMatrix *m)
{
	printf("[\n");
	for (int col = 0; col < m->dim; col++) {
		printf("\t");
		for (int row = 0; row < m->dim; row++) {
			if (row == 0) {
				printf("%lf", m->value[col][row]);
			} else {
				printf(" %lf", m->value[col][row]);
			}
		}
		printf("\n");
	}
	printf("]\n");
}

KMatrix *KMat_dot(const KMatrix *x, const KMatrix *y)
{
	if (x->dim != y->dim) {
		return NULL;
	}
	KMatrix *res = KMat_zeros(x->dim);
	for (int row = 0; row < x->dim; row++) {
		for (int col = 0; col < x->dim; col++) {
			for (int i = 0; i < x->dim; i++) {
				res->value[row][col] +=
					x->value[row][i] * y->value[i][col];
			}
		}
	}
	return res;
}

KMatrix *KMat_inverse(const KMatrix *m)
{
	// TODO
	KMatrix *res = KMat_zeros(m->dim);
	return res;
}
