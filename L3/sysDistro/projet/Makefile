CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Werror -posix 
LDFLAGS=
LDLIBS=-lpthread
RM=rm -rfv

OBJ=obj
BIN=bin
SRC=src
OBJ_UTIL=$(OBJ)/utils
SRC_UTIL=$(SRC)/utils

CLIENT_OBJS=$(OBJ_UTIL)/util.o $(OBJ_UTIL)/request.o $(OBJ_UTIL)/logger.o
BARMAN_OBJS=$(OBJ_UTIL)/util.o $(OBJ_UTIL)/request.o $(OBJ_UTIL)/tap.o $(OBJ_UTIL)/process.o $(OBJ_UTIL)/pipe.o $(OBJ_UTIL)/logger.o
TIREUSES_OBJS=$(OBJ_UTIL)/util.o $(OBJ_UTIL)/tap.o $(OBJ_UTIL)/logger.o

.PHONY: all clean

all: $(BIN)/barman.out $(BIN)/client.out $(BIN)/tireuses.out
barman: $(BIN)/barman.out
client: $(BIN)/client.out
tireuses: $(BIN)/tireuses.out


$(OBJ)/utils/%.o: $(SRC_UTIL)/%.c $(SRC_UTIL)/%.h | $(OBJ_UTIL)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<


$(BIN)/client.out: $(OBJ)/client.o $(CLIENT_OBJS) | $(BIN)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(BIN)/barman.out: $(OBJ)/barman.o $(BARMAN_OBJS) | $(BIN)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(BIN)/tireuses.out: $(OBJ)/tireuses.o $(TIREUSES_OBJS) | $(BIN)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)


$(OBJ):
	mkdir -p $@

$(OBJ_UTIL):
	mkdir -p $@

$(BIN):
	mkdir -p $@

clean:
	$(RM) $(OBJ) $(BIN)