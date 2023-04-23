# Python 3 interface of KMatrix

> A wrapper of KMatrix in Python 3 using ctypes

All the functions doesn't make changes in-place.

**Note**: Although one can call `KMatrix(...)` or `KArray(...)`
to create a new instance, this is not recommended.
Instead, use functions such as `ones()` and `from_2darray()`

## `KMatrix`

Create KMatrix filled with 0
```python3
zeros(dim: int) -> KMatrix:
```

Create KMatrix filled with 0
```python3
ones(dim: int) -> KMatrix:
```

Create a KMatrix with principal diagonal set to 1, and other elements set to 0
```python3
eye(dim: int) -> KMatrix:
```

Deep copy
```python3
copy(self) -> KMatrix:
```

Get the transpose of a KMatrix
```python3
T(self) -> KMatrix:
```

Dot product of two KMatrix
```python3
dot(self, other: KMatrix) -> KMatrix:
```

Get the inverse of a KMatrix, using LU decomposition
```python3
inv(self) -> KMatrix:
```

Get the determinant of a KMatrix
```python3
det(self) -> float:
```

Get the trace of a KMatrix
```python3
trace(self) -> float:
```

Get the rank of a KMatrix
```python3
rank(self) -> int:
```

Get the sum of all elements of a KMatrix
```python3
sum(self) -> float:
```

Get the mean of all elements of a KMatrix
```python3
mean(self) -> float:
```

Get the variance of all elements of a KMatrix
```python3
var(self) -> float:
```

Get the standard deviation of all elements of a KMatrix
```python3
std(self) -> float:
```

Get the minimum of all elements of a KMatrix
```python3
min(self) -> float:
```

Get the maximum of all elements of a KMatrix
```python3
max(self) -> float:
```

Turn a KMatrix into a KArray
```python3
toKArray(self) -> KArray:
```

Print KMatrix
```python3
display(self) -> None:
```

## `KArray`

Create a KArray with all elements set to 0
```python3
zeros(shape: tuple(int, int)) -> KArray:
```

Create a KArray with all elements set to 1
```python3
ones(shape: tuple(int, int)) -> KArray:
```

Create a KArray from a 2d list,
if the length of each sub-lists mismatch,
this will extend short sub-lists with 0
```python3
from_2darray(values: list[list[float]]) -> KArray:
```

Set the value of a KArray at (col, row)
```python3
set(self, col: int, row: int, value: float) -> None:
```

Get the value of a KArray at (col, row)
```python3
get(self, col: int, row: int) -> float:
```

Get the transpose of a KArray
```python3
T(self) -> KArray:
```

Dot product of two KArray
```python3
dot(self, other: KArray) -> KArray:
```

Turn a KArray into a KMatrix
```python3
toKMatrix(self) -> KMatrix:
```

Add two KArray by element
```python3
add(self, other: KArray) -> KArray:
```

Subtract two KArray by element
```python3
sub(self, other: KArray) -> KArray:
```

Multiply two KArray by element
```python3
mul(self, other: KArray) -> KArray:
```

Divide two KArray by element
```python3
div(self, other: KArray) -> KArray:
```

Add all elements of a KArray by a number
```python3
addnum(self, num: float) -> KArray:
```

Subtract all elements of a KArray by a number
```python3
subnum(self, num: float) -> KArray:
```

Multiply all elements of a KArray by a number
```python3
mulnum(self, num: float) -> KArray:
```

Divide all elements of a KArray by a number
```python3
divnum(self, num: float) -> KArray:
```

If two KArray are equal
```python3
equals(self, other: KArray) -> bool:
```

Reshape a KArray,
if the new shape is not compatible with the old shape,
add 0 to the new KArray when larger,
or delete elements when smaller
```python3
reshape(self, shape: tuple(int, int)) -> KArray:
```

Get the sum of all elements of a KArray
```python3
sum(self) -> float:
```

Get the mean of all elements of a KArray
```python3
mean(self) -> float:
```

Get the variance of all elements of a KArray
```python3
var(self) -> float:
```

Get the standard deviation of all elements of a KArray
```python3
std(self) -> float:
```

Get the minimum of all elements of a KArray
```python3
min(self) -> float:
```

Get the maximum of all elements of a KArray
```python3
max(self) -> float:
```

Get the rank of a KArray
```python3
rank(self) -> int:
```

Print a KArray
```python3
display(self) -> None:
```

