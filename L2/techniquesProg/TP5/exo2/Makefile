CC=gcc
CFLAGS=-std=c89 -pedantic -Wall -Werror -g
LDFLAGS=
LDLIBS=-lm
RM= rm -fv

.PHONY: all clean

all: quadratic-equation.out
quadratic-equation.out: quadratic-equation.c 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) *.o *.out
