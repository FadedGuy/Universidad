CC=gcc
CFLAGS=-std=c89 -pedantic -Wall -Werror -g
LDFLAGS=
LDLIBS=
RM=rm -fv

all: main.out
book.o: book.c book.h
	$(CC) $(CFLAGS) -c -o book.o book.c
library.o: library.c library.h
	$(CC) $(CFLAGS) -c -o library.o library.c
main.out: main.c book.o library.o
	$(CC) $(CFLAGS) -o main.out main.c book.o library.o $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) *.o *.out
