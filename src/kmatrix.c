#include "kmatrix.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

KMatrix *KMat_create(const size_t dim, KM_DATA **value)
{
	KMatrix *res = (KMatrix *)malloc(sizeof(KMatrix));
	res->dim = dim;
	res->value = (KM_DATA **)malloc(sizeof(KM_DATA *) * dim);
	for (int i = 0; i < dim; i++) {
		res->value[i] = (KM_DATA *)malloc(sizeof(KM_DATA) * dim);
		for (int j = 0; j < dim; j++) {
			res->value[i][j] = *((KM_DATA *)value + dim * i + j);
		}
	}
	return res;
}

KMatrix *KMat_copy(const KMatrix *m)
{
	KMatrix *res = (KMatrix *)malloc(sizeof(KMatrix));
	res->dim = m->dim;
	res->value = (KM_DATA **)malloc(sizeof(KM_DATA *) * m->dim);
	for (int i = 0; i < m->dim; i++) {
		res->value[i] = (KM_DATA *)malloc(sizeof(KM_DATA) * m->dim);
		for (int j = 0; j < m->dim; j++) {
			res->value[i][j] = m->value[i][j];
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
				printf("%Lf", m->value[col][row]);
			} else {
				printf(" %Lf", m->value[col][row]);
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

KM_DATA KMat_determinant(const KMatrix *m)
{
	if (m->dim == 1) {
		return m->value[0][0];
	}
	KM_DATA s = 0;
	KMatrix *subm = KMat_zeros(m->dim - 1);
	int f = -1;
	for (int k = 0; k < m->dim; k++) {
		for (int i = 1; i < m->dim; i++) {
			for (int j = 0; j < m->dim; j++) {
				if (j < k) {
					subm->value[i - 1][j] = m->value[i][j];
				} else if (j > k) {
					subm->value[i - 1][j - 1] =
						m->value[i][j];
				}
			}
		}
		f = -f;
		s += f * m->value[0][k] * KMat_determinant(subm);
	}
	KMat_delete(subm);
	return s;
}

KM_DATA KMat_trace(const KMatrix *m)
{
	KM_DATA tr = 0;
	for (int i = 0; i < m->dim; i++) {
		tr += m->value[i][i];
	}
	return tr;
}

size_t KMat_rank(const KMatrix *m)
{
	// TODO
}

KM_DATA KMat_norm(const KMatrix *m)
{
	// TODO
}

KM_DATA KMat_sum(const KMatrix *m)
{
	KM_DATA s = 0;
	for (int i = 0; i < m->dim; i++) {
		for (int j = 0; j < m->dim; j++) {
			s += m->value[i][j];
		}
	}
	return s;
}

KM_DATA KMat_mean(const KMatrix *m)
{
	return KMat_sum(m) / (m->dim * m->dim);
}

KM_DATA KMat_var(const KMatrix *m)
{
	KM_DATA mean = KMat_mean(m);
	KM_DATA s = 0;
	for (int i = 0; i < m->dim; i++) {
		for (int j = 0; j < m->dim; j++) {
			s += (m->value[i][j] - mean) * (m->value[i][j] - mean);
		}
	}
	return s / (m->dim * m->dim);
}

KM_DATA KMat_std(const KMatrix *m)
{
	return sqrt(KMat_var(m));
}

KM_DATA KMat_min(const KMatrix *m)
{
	KM_DATA min = m->value[0][0];
	for (int i = 0; i < m->dim; i++) {
		for (int j = 0; j < m->dim; j++) {
			if (m->value[i][j] < min) {
				min = m->value[i][j];
			}
		}
	}
	return min;
}

KM_DATA KMat_max(const KMatrix *m)
{
	KM_DATA max = m->value[0][0];
	for (int i = 0; i < m->dim; i++) {
		for (int j = 0; j < m->dim; j++) {
			if (m->value[i][j] > max) {
				max = m->value[i][j];
			}
		}
	}
	return max;
}

// L Matrix inverse
KMatrix *L_inverse(const KMatrix *m)
{
	KMatrix *res = KMat_zeros(m->dim);
	int n = m->dim;
	for (int i = 1; i <= n; i++) {
		res->value[i - 1][i - 1] = 1 / m->value[i - 1][i - 1];
		for (int j = 1; j <= i - 1; j++) {
			KM_DATA s = 0;
			for (int k = j; k <= i - 1; k++) {
				s += m->value[i - 1][k - 1] *
				     res->value[k - 1][j - 1];
			}
			res->value[i - 1][j - 1] =
				-s * res->value[i - 1][i - 1];
		}
	}
	return res;
}

KMatrix *KMat_inverse(const KMatrix *m)
{
	KMatrix *L = KMat_eye(m->dim);
	KMatrix *U = KMat_zeros(m->dim);
	for (int i = 0; i < m->dim; i++) {
		U->value[0][i] = m->value[0][i];
	}
	// calculate L and U
	for (int j = 0; j <= m->dim - 2; j++) {
		for (int i = j + 1; i <= m->dim - 1; i++) {
			L->value[i][j] = m->value[i][j];
			for (int k = 0; k <= j - 1; k++) {
				L->value[i][j] -=
					L->value[i][k] * U->value[k][j];
			}
			L->value[i][j] /= U->value[j][j];
		}
		for (int i = j + 1; i <= m->dim - 1; i++) {
			int i_u, j_u;
			i_u = j + 1;
			j_u = i;
			U->value[i_u][j_u] = m->value[i_u][j_u];
			for (int k = 0; k <= i_u - 1; k++) {
				U->value[i_u][j_u] -=
					L->value[i_u][k] * U->value[k][j_u];
			}
		}
	}
	KM_DATA nultmp = 1;
	for (int i = 0; i < m->dim; i++) {
		nultmp *= U->value[i][i];
	}
	if (nultmp == 0) {
		return NULL;
	}
	// calculate LI(inverse of L)
	KMatrix *LI = KMat_eye(m->dim);
	for (int i = 0; i < m->dim; i++) {
		for (int k = i + 1; k < m->dim; k++) {
			for (int j = i; j <= k - 1; j++)
				LI->value[k][i] -=
					L->value[k][j] * LI->value[j][i];
		}
	}
	KMat_delete(L);
	// calculate UI(inverse of U)
	KMatrix *UT = KMat_T(U);
	KMat_delete(U);
	KMatrix *UTI = L_inverse(UT);
	KMat_delete(UT);
	KMatrix *UI = KMat_T(UTI);
	KMat_delete(UTI);
	KMatrix *mI = KMat_dot(UI, LI);
	KMat_delete(LI);
	KMat_delete(UI);
	return mI;
}

KArray *KMat_toKArr(const KMatrix *m)
{
	// TODO: test this
	KArray *res = KArr_zeros(m->dim, m->dim);
	for (int i = 0; i < m->dim; i++) {
		for (int j = 0; j < m->dim; j++) {
			KArr_set(res, i, j, m->value[i][j]);
		}
	}
	return res;
}

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

KArray *KArr_reshape(const KArray *a, const size_t shape0, const size_t shape1)
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

KM_DATA KArr_sum(const KArray *a)
{
	KM_DATA sum = 0;
	for (int i = 0; i < a->shape0 * a->shape1; i++) {
		sum += a->value[i];
	}
	return sum;
}

KM_DATA KArr_mean(const KArray *a)
{
	return KArr_sum(a) / (a->shape0 * a->shape1);
}

KM_DATA KArr_var(const KArray *a)
{
	KM_DATA mean = KArr_mean(a);
	KM_DATA var = 0;
	for (int i = 0; i < a->shape0 * a->shape1; i++) {
		var += (a->value[i] - mean) * (a->value[i] - mean);
	}
	return var / (a->shape0 * a->shape1);
}

KM_DATA KArr_std(const KArray *a)
{
	return sqrt(KArr_var(a));
}

KM_DATA KArr_min(const KArray *a)
{
	KM_DATA min = a->value[0];
	for (int i = 0; i < a->shape0 * a->shape1; i++) {
		if (a->value[i] < min) {
			min = a->value[i];
		}
	}
	return min;
}

KM_DATA KArr_max(const KArray *a)
{
	KM_DATA max = a->value[0];
	for (int i = 0; i < a->shape0 * a->shape1; i++) {
		if (a->value[i] > max) {
			max = a->value[i];
		}
	}
	return max;
}

size_t KArr_rank(const KArray *a)
{
	// TODO
}
