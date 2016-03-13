# Simple makefile for building test cases

CC       = gcc
LINK     = gcc

CFLAGS   = -Wall -std=gnu99 -ggdb

OBJECTS  = strutil.o vlenc.o test-main.o
TARGET   = test-main

$(TARGET): $(OBJECTS)
	$(LINK) $(LFLAGS) -o $@ $(OBJECTS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS) *~

# deps:
vlenc.o: vlenc.c vlenc.h
strutil.o: strutil.c strutil.h
test-main.o: test-main.c strutil.h vlenc.h
