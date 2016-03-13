# Simple makefile for building test cases

CC       = gcc
CXX      = g++
LINK     = gcc

CFLAGS   = -Wall -std=gnu99 -ggdb
CXXFLAGS = -std=c++11 -Wall -ggdb

OBJECTS  = strutil.o vlenc.o
TARGET   = test-main

test-cxx: $(OBJECTS) test-cxx.cc
	$(CXX) $(CXXFLAGS) -o $@ test-cxx.cc $(OBJECTS)

$(TARGET): $(OBJECTS) test-main.c
	$(LINK) $(LFLAGS) -o $@ test-main.c $(OBJECTS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS) *~

# deps:
vlenc.o: vlenc.c vlenc.h
strutil.o: strutil.c strutil.h
test-main.o: test-main.c strutil.h vlenc.h
