all: main.out
library.o: library.cpp library.h
	g++ -std=c++98 -pedantic -Wall -Werror -g -c -o library.o library.cpp
book.o: book.cpp book.h
	g++ -std=c++98 -pedantic -Wall -Werror -g -c -o book.o book.cpp
main.out: main.cpp library.o book.o
	g++ -std=c++98 -pedantic -Wall -Werror -g -o main.out main.cpp library.o book.o

clean:
	rm -fv *.o *.out
