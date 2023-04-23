# C interface of KMatrix

## Structs and Datatype

KMatrix is a (dim x dim) square matrix.
```c
typedef struct {
    size_t dim;
    KM_DATA **value;
} KMatrix;
```

KArray is a (shape0 x shape1) 2 dimension array.
```c
typedef struct {
    size_t shape0;
    size_t shape1;
    KM_DATA *value;
} KArray;
```

The data type KMatrix use is `long double`
```c
#define KM_DATA long double
```

## Functions

All the operations on `KMatrix` and `KArray` are not in-place.

### `KMatrix`

Create a KMatrix
```c
KMatrix *KMat_create(const size_t dim, KM_DATA **value);
```

Get deep copy of KMatrix
```c
KMatrix *KMat_copy(const KMatrix *m);
```

Create a KMatrix with all elements set to 0
```c
KMatrix *KMat_zeros(const size_t dim);
```

Create a KMatrix with all elements set to 1
```c
KMatrix *KMat_ones(const size_t dim);
```

Create a KMatrix with principal diagonal set to 1, and other elements set to 0
```c
KMatrix *KMat_eye(const size_t dim);
```

Delete a KMatrix, collect memory
```c
void KMat_delete(KMatrix *m);
```

Get the transpose of a KMatrix
```c
KMatrix *KMat_T(const KMatrix *m);
```

Print a KMatrix
```c
void KMat_print(const KMatrix *m);
```

Dot product of two KMatrix
```c
KMatrix *KMat_dot(const KMatrix *x, const KMatrix *y);
```

Get the inverse of a KMatrix, using LU decomposition
```c
KMatrix *KMat_inverse(const KMatrix *m);
```

Get the determinant of a KMatrix
```c
KM_DATA KMat_determinant(const KMatrix *m);
```

Get the trace of a KMatrix
```c
KM_DATA KMat_trace(const KMatrix *m);
```

Get the rank of a KMatrix
```c
size_t KMat_rank(const KMatrix *m);
```

Get the sum of all elements of a KMatrix
```c
KM_DATA KMat_sum(const KMatrix *m);
```

Get the mean of all elements of a KMatrix
```c
KM_DATA KMat_mean(const KMatrix *m);
```

Get the variance of all elements of a KMatrix
```c
KM_DATA KMat_var(const KMatrix *m);
```

Get the standard deviation of all elements of a KMatrix
```c
KM_DATA KMat_std(const KMatrix *m);
```

Get the minimum of all elements of a KMatrix
```c
KM_DATA KMat_min(const KMatrix *m);
```

Get the maximum of all elements of a KMatrix
```c
KM_DATA KMat_max(const KMatrix *m);
```

Turn a KMatrix into a KArray
```c
KArray *KMat_toKArr(const KMatrix *m);
```

### `KArray`

Create a KArray
```c
KArray *KArr_create(const size_t shape0, const size_t shape1, KM_DATA *value);
```

Deep copy of a KArray
```c
KArray *KArr_copy(const KArray *a);
```

Create a KArray with all elements set to 0
```c
KArray *KArr_zeros(const size_t shape0, const size_t shape1);
```

Create a KArray with all elements set to 1
```c
KArray *KArr_ones(const size_t shape0, const size_t shape1);
```

Set the value of a KArray at (col, row)
```c
bool KArr_set(const KArray *a, const size_t col, const size_t row, KM_DATA value);
```

Get the value of a KArray at (col, row)
```c
KM_DATA KArr_get(const KArray *a, const size_t col, const size_t row);
```

Delete a KArray, collect memory
```c
void KArr_delete(KArray *a);
```

Get the transpose of a KArray
```c
KArray *KArr_T(const KArray *a);
```

Print a KArray
```c
void KArr_print(const KArray *a);
```

Dot product of two KArray
```c
KArray *KArr_dot(const KArray *x, const KArray *y);
```

Turn a KArray into a KMatrix
```c
KMatrix *KArr_toKMat(const KArray *a);
```

Add two KArray by element,
returns NULL and print stderr if
the shape of a and b mismatch
```c
KArray *KArr_add(const KArray *a, const KArray *b);
```

Subtract two KArray by element,
returns NULL and print stderr if
the shape of a and b mismatch
```c
KArray *KArr_sub(const KArray *a, const KArray *b);
```

Multiply two KArray by element,
returns NULL and print stderr if
the shape of a and b mismatch
```c
KArray *KArr_mul(const KArray *a, const KArray *b);
```

Divide two KArray by element,
returns NULL and print stderr if
the shape of a and b mismatch
```c
KArray *KArr_div(const KArray *a, const KArray *b);
```

Add all elements of a KArray by a number
```c
KArray *KArr_addnum(const KArray *a, const KM_DATA b);
```

Subtract all elements of a KArray by a number
```c
KArray *KArr_subnum(const KArray *a, const KM_DATA b);
```

Multiply all elements of a KArray by a number
```c
KArray *KArr_mulnum(const KArray *a, const KM_DATA b);
```

Divide all elements of a KArray by a number
```c
KArray *KArr_divnum(const KArray *a, const KM_DATA b);
```

If two KArray are equal,
print to stderr if shape of a and b mismatch
```c
bool KArr_equal(const KArray *a, const KArray *b);
```

Reshape a KArray,
if the new shape is not compatible with the old shape,
add 0 to the new KArray when larger,
or delete elements when smaller
```c
KArray *KArr_reshape(const KArray *a, const size_t shape0, const size_t shape1);
```

Get the sum of all elements of a KArray
```c
KM_DATA KArr_sum(const KArray *a);
```

Get the mean of all elements of a KArray
```c
KM_DATA KArr_mean(const KArray *a);
```

Get the variance of all elements of a KArray
```c
KM_DATA KArr_var(const KArray *a);
```

Get the standard deviation of all elements of a KArray
```c
KM_DATA KArr_std(const KArray *a);
```

Get the minimum of all elements of a KArray
```c
KM_DATA KArr_min(const KArray *a);
```

Get the maximum of all elements of a KArray
```c
KM_DATA KArr_max(const KArray *a);
```

Get the rank of a KArray
```c
size_t KArr_rank(const KArray *a);
```

