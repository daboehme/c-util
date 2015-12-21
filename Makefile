# Simple makefile for building test cases

CC       = gcc
LINK     = gcc

CFLAGS   = -Wall -std=gnu99 -ggdb

OBJECTS  = strutil.o test-main.o
TARGET   = test-main

$(TARGET): $(OBJECTS)
	$(LINK) $(LFLAGS) -o $@ $(OBJECTS)

%.o : %.c strutil.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS) *~

