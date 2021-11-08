all: main.out
book.o: book.c book.h
	gcc -std=c89 -pedantic -Wall -Werror -g -c -o book.o book.c
library.o: library.c library.h
	gcc -std=c89 -pedantic -Wall -Werror -g -c -o library.o library.c
main.out: main.c book.o library.o
	gcc -std=c89 -pedantic -Wall -Werror -g -o main.out main.c book.o library.o

clean:
	rm -fv *.o *.out

