CC=gcc
CFLAGS=
LDFLAGS=
LDLIBS=
RM=rm -fv

.PHONY: server client clean

server: server.out
client: client_tcp.out

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
server.out: serveur.c fonction.o calculs.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)
client_tcp.out: client_tcp.c fonction.o calculs.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) *.o *.out