CXX=g++
CXXFLAGS=-std=c++98 -pedantic -Wall -Werror -g `pkg-config pugixml --cflags`
LDFLAGS=`pkg-config pugixml --libs-only-L`
LDLIBS=`pkg-config pugixml --libs-only-l`
RM= rm -fv
.PHONY: all clean

all: edp.out
edp.out: edp.cpp address.o company.o envelope.o envelope-c4.o envelope-dl.o  str2i-error.o str2l-error.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) *.o *.out
