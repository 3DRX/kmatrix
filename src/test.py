from kmatrix import KArray

if __name__ == "__main__":
    km = KArray.from_values((3, 3), [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12])
    km.display()
    km2 = km.copy()
    km2.display()
    pass
