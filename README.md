# KMatrix

> A toy matrix library in C

This is a matrix library written in C and provides API in both Python 3 and C.

## Usage
- [C](./doc/c.md)
- [Python 3](./doc/python.md)

## Build
1. `cd` into the src folder.
2. `make build` generates libkmatrix.so which can be used in Python 3.

## Demo

Demo in Python 3

```python3
from kmatrix import KArray

if __name__ == "__main__":
    kr = KArray.from_values((3, 3), [1, 5, 3, 5, 7, 5, 3, 3, 2])
    kr.display()
    kr.toKMatrix()\
        .inv()\
        .toKArray()\
        .display()
    pass
```

