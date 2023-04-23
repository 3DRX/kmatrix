from kmatrix import KArray

if __name__ == "__main__":
    kr = KArray.from_2darray(
        [
            [1, 2, 3],
            [6, 3, 7],
            [10, 345, 7]
        ]
    )
    kr.display()
    kr.toKMatrix()\
        .inv()\
        .toKArray()\
        .display()
    pass
