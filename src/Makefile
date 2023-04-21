
main:
	gcc kmatrix.c kmatrix.h test.c && ./a.out

dbg:
	gcc -fsanitize=undefined -fsanitize=address kmatrix.c kmatrix.h test.c && ./a.out

clean:
	rm kmatrix.h.gch a.out
