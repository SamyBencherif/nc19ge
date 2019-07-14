
CC=gcc
CFLAGS=-Wall -std=c89 -Werror# -v

AR=ar
ARFLAGS=-rs

all: examples

library src/ include/:
	$(CC) $(CFLAGS) -o bin/nc19ge.o -Iinclude -c src/nc19ge.c
	$(AR) $(ARFLAGS) bin/libnc19ge.a bin/nc19ge.o

examples examples/: library
	$(CC) $(CFLAGS) -o bin/frogs -Lbin -lncurses -lnc19ge -I include examples/frogs.c
