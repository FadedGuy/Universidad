CXX=g++
CXXFLAGS=-std=c++98 -pedantic -Wall -Werror -g
LDFLAGS=
LDLIBS=
RM= rm -fv

all: main.out
library.o: library.cpp library.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
book.o: book.cpp book.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
main.out: main.cpp library.o book.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) *.o *.out
