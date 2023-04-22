from kmatrix import KArray

if __name__ == "__main__":
    kr = KArray.from_values((3, 3), [1, 5, 3, 5, 7, 5, 3, 3, 2])
    print(type(kr))
    kr.display()
    kr.toKMatrix()\
        .inv()\
        .toKArray()\
        .display()
    pass
