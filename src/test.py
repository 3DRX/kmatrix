from kmatrix import KArray

if __name__ == "__main__":
    kr = KArray.from_values((3, 3), [1, 5, 3, 5, 7, 5, 3, 3, 2])
    kr.display()
    kr.toKMatrix()\
        .inv()\
        .toKArray()\
        .display()
    pass
