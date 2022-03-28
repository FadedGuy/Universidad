CXX=g++
CXXFLAGS=-std=c++98 -pedantic -Wall -Werror -g `pkg-config pugixml --cflags`
LDFLAGS=`pkg-config pugixml --libs-only-L`
LDLIBS=`pkg-config pugixml --libs-only-l`
RM= rm -fv
.PHONY: all clean

all: pugixml.out
pugixml.out: pugixml.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) *.o *.out
