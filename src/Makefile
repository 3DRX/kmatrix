
main:
	gcc -Wall datastructs.h karray.c karray.h kmatrix.c kmatrix.h test.c && ./a.out

dbg:
	gcc -Wall -fsanitize=undefined -fsanitize=address datastructs.h karray.c karray.h kmatrix.c kmatrix.h test.c && ./a.out

clean:
	rm kmatrix.h.gch a.out karray.h.gch datastructs.h.gch
