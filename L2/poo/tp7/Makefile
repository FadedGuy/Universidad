CXX=g++
CXXFLAGS=-std=c++98 -pedantic -Wall -Werror -g
LDFLAGS=
LDLIBS=
RM= rm -fv
.PHONY: all clean

all: main.out
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
main.out: main.cpp library.o book.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) *.o *.out
