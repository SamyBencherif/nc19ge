
CC=gcc
CFLAGS=-Wall -std=c89 -Werror# -v

AR=ar
ARFLAGS=-rs

all: library examples

library src/ include/:
	$(CC) $(CFLAGS) -o bin/ncknge.o -Iinclude -c src/ncknge.c
	$(AR) $(ARFLAGS) bin/libncknge.a bin/ncknge.o

examples examples/:
	$(CC) $(CFLAGS) -o bin/examples/frogs -Lbin -I include src/examples/frogs.c -lncurses -lncknge -lm

clean:
	rm -r bin/*
