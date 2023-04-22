import ctypes
from __future__ import annotations

C_library = ctypes.CDLL("./libkmatrix.so")


class KMatrix(ctypes.Structure):
    _fields_ = [
        ("dim", ctypes.c_size_t),
        ("value", ctypes.POINTER(
            ctypes.POINTER(ctypes.c_longdouble)))
    ]

    def __init__(self, dim, type="zeros", values=None):
        if type == "zeros":
            self.obj = C_library.KMat_zeros(dim)
        elif type == "ones":
            self.obj = C_library.KMat_ones(dim)
        elif type == "eye":
            self.obj = C_library.KMat_eye(dim)
        elif type == "obj":
            self.obj = values
        else:
            raise Exception("Unknown type: {}".format(type))
        pass

    def __del__(self):
        try:
            C_library.KMat_delete(self.obj)
        except:
            pass

    def zeros(dim: int) -> KMatrix:
        return KMatrix(dim, type="zeros")

    def ones(dim: int) -> KMatrix:
        return KMatrix(dim, type="ones")

    def eye(dim: int) -> KMatrix:
        return KMatrix(dim, type="eye")

    def copy(self) -> KMatrix:
        KMat_copy = C_library.KMat_copy
        KMat_copy.restype = ctypes.POINTER(KMatrix)
        tmp = KMat_copy(self.obj)
        return KMatrix(
            tmp.contents.dim,
            type="obj",
            values=tmp
        )

    def T(self) -> KMatrix:
        KMat_T = C_library.KMat_T
        KMat_T.restype = ctypes.POINTER(KMatrix)
        tmp = KMat_T(self.obj)
        return KMatrix(
            tmp.contents.dim,
            type="obj",
            values=tmp
        )

    def dot(self, other: KMatrix) -> KMatrix:
        KMat_dot = C_library.KMat_dot
        KMat_dot.restype = ctypes.POINTER(KMatrix)
        tmp = KMat_dot(self.obj, other.obj)
        return KMatrix(
            tmp.contents.dim,
            type="obj",
            values=tmp
        )

    def inv(self) -> KMatrix:
        KMat_inverse = C_library.KMat_inverse
        KMat_inverse.restype = ctypes.POINTER(KMatrix)
        tmp = KMat_inverse(self.obj)
        if not tmp:
            raise Exception("Matrix is singular")
        return KMatrix(
            tmp.contents.dim,
            type="obj",
            values=tmp
        )

    def det(self) -> float:
        KMat_determinant = C_library.KMat_determinant
        KMat_determinant.restype = ctypes.c_longdouble
        return KMat_determinant(self.obj)

    def trace(self) -> float:
        KMat_trace = C_library.KMat_trace
        KMat_trace.restype = ctypes.c_longdouble
        return KMat_trace(self.obj)

    def rank(self) -> int:
        KMat_rank = C_library.KMat_rank
        KMat_rank.restype = ctypes.c_size_t
        return KMat_rank(self.obj)

    def norm(self) -> float:
        KMat_norm = C_library.KMat_norm
        KMat_norm.restype = ctypes.c_longdouble
        return KMat_norm(self.obj)

    def sum(self) -> float:
        KMat_sum = C_library.KMat_sum
        KMat_sum.restype = ctypes.c_longdouble
        return KMat_sum(self.obj)

    def mean(self) -> float:
        KMat_mean = C_library.KMat_mean
        KMat_mean.restype = ctypes.c_longdouble
        return KMat_mean(self.obj)

    def var(self) -> float:
        KMat_var = C_library.KMat_var
        KMat_var.restype = ctypes.c_longdouble
        return KMat_var(self.obj)

    def std(self) -> float:
        KMat_std = C_library.KMat_std
        KMat_std.restype = ctypes.c_longdouble
        return KMat_std(self.obj)

    def min(self) -> float:
        KMat_min = C_library.KMat_min
        KMat_min.restype = ctypes.c_longdouble
        return KMat_min(self.obj)

    def max(self) -> float:
        KMat_max = C_library.KMat_max
        KMat_max.restype = ctypes.c_longdouble
        return KMat_max(self.obj)

    def toKArray(self) -> KArray:
        KMat_toKArr = C_library.KMat_toKArr
        KMat_toKArr.restype = ctypes.POINTER(KArray)
        tmp = KMat_toKArr(self.obj)
        return KArray(
            (tmp.contents.shape0, tmp.contents.shape1),
            type="obj",
            values=tmp
        )

    def display(self) -> None:
        C_library.KMat_print(self.obj)
        pass
    pass


class KArray(ctypes.Structure):
    _fields_ = [
        ("shape0", ctypes.c_size_t),
        ("shape1", ctypes.c_size_t),
        ("value", ctypes.POINTER(ctypes.c_longdouble))
    ]

    def __init__(self, shape, type="zeros", values=None):
        if type == "zeros":
            self.obj = C_library.KArr_zeros(shape[0], shape[1])
        elif type == "ones":
            self.obj = C_library.KArr_ones(shape[0], shape[1])
        elif type == "values":
            if values is None:
                raise Exception("Values must be provided")
            else:
                arr = (ctypes.c_longdouble * len(values))(*values)
                self.obj = C_library.KArr_create(
                    shape[0], shape[1], arr)
                pass
        elif type == "obj":
            self.obj = values
        else:
            raise Exception("Unknown type: {}".format(type))
        pass

    def __del__(self):
        try:
            C_library.KArr_delete(self.obj)
        except:
            pass

    def zeros(shape: tuple(int, int)) -> KArray:
        return KArray(shape, type="zeros")

    def ones(shape: tuple(int, int)) -> KArray:
        return KArray(shape, type="ones")

    def from_values(shape: tuple(int, int), values: list[float]) -> KArray:
        return KArray(shape, type="values", values=values)

    def copy(self) -> KArray:
        KArr_copy = C_library.KArr_copy
        KArr_copy.restype = ctypes.POINTER(KArray)
        tmp = KArr_copy(self.obj)
        return KArray(
            (tmp.contents.shape0,
             tmp.contents.shape1),
            type="obj",
            values=tmp
        )

    def set(self, col: int, row: int, value: float) -> None:
        Ldouble = (ctypes.c_longdouble)(value)
        C_library.KArr_set(self.obj, col, row, Ldouble)
        pass

    def get(self, col: int, row: int) -> float:
        KArr_get = C_library.KArr_get
        KArr_get.restype = ctypes.c_longdouble
        return KArr_get(self.obj, col, row)

    def T(self) -> KArray:
        KArr_T = C_library.KArr_T
        KArr_T.restype = ctypes.POINTER(KArray)
        tmp = KArr_T(self.obj)
        return KArray(
            (tmp.contents.shape0,
             tmp.contents.shape1),
            type="obj",
            values=tmp
        )

    def dot(self, other: KArray) -> KArray:
        KArr_dot = C_library.KArr_dot
        KArr_dot.restype = ctypes.POINTER(KArray)
        tmp = KArr_dot(self.obj, other.obj)
        return KArray(
            (tmp.contents.shape0,
             tmp.contents.shape1),
            type="obj",
            values=tmp
        )

    def toKMatrix(self) -> KMatrix:
        KArr_toKMat = C_library.KArr_toKMat
        KArr_toKMat.restype = ctypes.POINTER(KMatrix)
        tmp = KArr_toKMat(self.obj)
        if not tmp:
            raise Exception("Cannot convert to KMatrix")
        return KMatrix(
            tmp.contents.dim,
            type="obj",
            values=tmp
        )

    def add(self, other: KArray) -> KArray:
        KArr_add = C_library.KArr_add
        KArr_add.restype = ctypes.POINTER(KArray)
        tmp = KArr_add(self.obj, other.obj)
        return KArray(
            (tmp.contents.shape0,
             tmp.contents.shape1),
            type="obj",
            values=tmp
        )

    def sub(self, other: KArray) -> KArray:
        KArr_sub = C_library.KArr_sub
        KArr_sub.restype = ctypes.POINTER(KArray)
        tmp = KArr_sub(self.obj, other.obj)
        return KArray(
            (tmp.contents.shape0,
             tmp.contents.shape1),
            type="obj",
            values=tmp
        )

    def mul(self, other: KArray) -> KArray:
        KArr_mul = C_library.KArr_mul
        KArr_mul.restype = ctypes.POINTER(KArray)
        tmp = KArr_mul(self.obj, other.obj)
        return KArray(
            (tmp.contents.shape0,
             tmp.contents.shape1),
            type="obj",
            values=tmp
        )

    def div(self, other: KArray) -> KArray:
        KArr_div = C_library.KArr_div
        KArr_div.restype = ctypes.POINTER(KArray)
        tmp = KArr_div(self.obj, other.obj)
        return KArray(
            (tmp.contents.shape0,
             tmp.contents.shape1),
            type="obj",
            values=tmp
        )

    def addnum(self, num: float) -> KArray:
        KArr_addnum = C_library.KArr_addnum
        KArr_addnum.restype = ctypes.POINTER(KArray)
        tmp = KArr_addnum(self.obj, ctypes.c_longdouble(num))
        return KArray(
            (tmp.contents.shape0,
             tmp.contents.shape1),
            type="obj",
            values=tmp
        )

    def subnum(self, num: float) -> KArray:
        KArr_subnum = C_library.KArr_subnum
        KArr_subnum.restype = ctypes.POINTER(KArray)
        tmp = KArr_subnum(self.obj, ctypes.c_longdouble(num))
        return KArray(
            (tmp.contents.shape0,
             tmp.contents.shape1),
            type="obj",
            values=tmp
        )

    def mulnum(self, num: float) -> KArray:
        KArr_mulnum = C_library.KArr_mulnum
        KArr_mulnum.restype = ctypes.POINTER(KArray)
        tmp = KArr_mulnum(self.obj, ctypes.c_longdouble(num))
        return KArray(
            (tmp.contents.shape0,
             tmp.contents.shape1),
            type="obj",
            values=tmp
        )

    def divnum(self, num: float) -> KArray:
        KArr_divnum = C_library.KArr_divnum
        KArr_divnum.restype = ctypes.POINTER(KArray)
        tmp = KArr_divnum(self.obj, ctypes.c_longdouble(num))
        return KArray(
            (tmp.contents.shape0,
             tmp.contents.shape1),
            type="obj",
            values=tmp
        )

    def equals(self, other: KArray) -> bool:
        KArr_equal = C_library.KArr_equal
        KArr_equal.restype = ctypes.c_bool
        return KArr_equal(self.obj, other.obj)

    def reshape(self, shape: tuple(int, int)) -> KArray:
        KArr_reshape = C_library.KArr_reshape
        KArr_reshape.restype = ctypes.POINTER(KArray)
        tmp = KArr_reshape(self.obj, shape[0], shape[1])
        return KArray(
            (tmp.contents.shape0,
             tmp.contents.shape1),
            type="obj",
            values=tmp
        )

    def sum(self) -> float:
        KArr_sum = C_library.KArr_sum
        KArr_sum.restype = ctypes.c_longdouble
        return KArr_sum(self.obj)

    def mean(self) -> float:
        KArr_mean = C_library.KArr_mean
        KArr_mean.restype = ctypes.c_longdouble
        return KArr_mean(self.obj)

    def var(self) -> float:
        KArr_var = C_library.KArr_var
        KArr_var.restype = ctypes.c_longdouble
        return KArr_var(self.obj)

    def std(self) -> float:
        KArr_std = C_library.KArr_std
        KArr_std.restype = ctypes.c_longdouble
        return KArr_std(self.obj)

    def min(self) -> float:
        KArr_min = C_library.KArr_min
        KArr_min.restype = ctypes.c_longdouble
        return KArr_min(self.obj)

    def max(self) -> float:
        KArr_max = C_library.KArr_max
        KArr_max.restype = ctypes.c_longdouble
        return KArr_max(self.obj)

    def rank(self) -> int:
        KArr_rank = C_library.KArr_rank
        KArr_rank.restype = ctypes.c_size_t
        return KArr_rank(self.obj)

    def display(self) -> None:
        C_library.KArr_print(self.obj)
        pass
    pass
