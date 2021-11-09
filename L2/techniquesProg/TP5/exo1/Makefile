CC=gcc
CFLAGS=-std=c89 -pedantic -Wall -Werror -g
LDFLAGS=
LDLIBS=-lm
RM= rm -fv

.PHONY: all clean

all: pythagoras.out
pythagoras.out: pythagoras.c 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) *.o *.out
