
CC=gcc
CFLAGS=-Wall -std=c89 -Werror

AR=ar
ARFLAGS=-rs

all: examples

library nc19ge.c:
	$(CC) $(CFLAGS) -o bin/nc19ge.o -c src/nc19ge.c
	$(AR) $(ARFLAGS) bin/libnc19ge.a bin/nc19ge.o

examples bin/libnc19ge.a examples/: library
	$(CC) $(CFLAGS) -o bin/frogs -Lbin -lncurses -lnc19ge -Iinclude examples/frogs.c
