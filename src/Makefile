main:
	gcc -Wall kmatrix.c kmatrix.h test.c -lm && ./a.out

dbg:
	gcc -Wall -fsanitize=undefined -fsanitize=address kmatrix.c kmatrix.h test.c -lm && ./a.out

build:
	gcc -Wall -fPIC kmatrix.c kmatrix.h -lm -shared -o libkmatrix.so

clean:
	rm kmatrix.h.gch a.out
