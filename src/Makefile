
main:
	gcc -Wall kmatrix.c kmatrix.h test.c && ./a.out

dbg:
	gcc -Wall -fsanitize=undefined -fsanitize=address kmatrix.c kmatrix.h test.c && ./a.out

clean:
	rm kmatrix.h.gch a.out
