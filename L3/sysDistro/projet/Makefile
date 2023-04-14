CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Werror
LDFLAGS=
LDLIBS=
RM=rm -fv

.PHONY: barman client clean

barman: barman.out
client: client.out

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

client.out: client.c util.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

barman.out: barman.c util.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) *.o *.out