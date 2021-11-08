CC=gcc
CFLAGS=-std=c89 -pedantic -Wall -Werror -g
LDFLAGS=
LDLIBS=
RM=rm -fv

.PHONY: all clean

all: main.out
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
main.out: main.c book.o library.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) *.o *.out
