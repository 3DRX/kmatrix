from kmatrix import KArray

if __name__ == "__main__":
    kr = KArray.from_2darray(
        [
            [1, 2, 3],
            [2, 4, 6],
            [10, 345, 7]
        ]
    )
    kr.display()
    kr += 1
    kr.display()
    pass
