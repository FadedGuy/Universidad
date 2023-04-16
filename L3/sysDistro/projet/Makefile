CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Werror
LDFLAGS=
LDLIBS=
RM=rm -fv

.PHONY: barman client tireuses clean

barman: barman.out
client: client.out
tireuses: tireuses.out

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

client.out: client.c util.o request.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

barman.out: barman.c util.o request.o tap.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

tireuses.out: tireuses.c util.o tap.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) *.o *.out