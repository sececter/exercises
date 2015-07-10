# Name:     complex.Makefile
# Author:   Leo Liberti
# Purpose:  makefile for complex class project
# Source:   GNU C++
# History:  061019 work started

CXXFLAGS = -g

all: test

test: complex.o test.cpp
	c++ $(CXXFLAGS) -o test test.cpp complex.o

complex.o: complex.cpp complex.h
	c++ $(CXXFLAGS) -c -o complex.o complex.cpp

clean:
	rm -f *~ complex.o test
