#include "kmatrix.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
