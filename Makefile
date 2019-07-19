
CC=gcc
CFLAGS=-Wall -std=c89 -Werror# -v

AR=ar
ARFLAGS=-rs

all: examples

library src/ include/:
	$(CC) $(CFLAGS) -o bin/ncknge.o -Iinclude -c src/ncknge.c
	$(AR) $(ARFLAGS) bin/libncknge.a bin/ncknge.o

examples examples/: library
	$(CC) $(CFLAGS) -o bin/frogs -Lbin -I include examples/frogs.c -lncurses -lncknge -lm
