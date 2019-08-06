
CC=gcc
CFLAGS=-Wall -std=c89 -Werror# -v

AR=ar
ARFLAGS=-rs

all: library tools examples

library src/ include/:
	$(CC) $(CFLAGS) -o bin/ncknge.o -Iinclude -c src/ncknge.c
	$(AR) $(ARFLAGS) bin/libncknge.a bin/ncknge.o
	-mkdir bin/examples
	-mkdir bin/tools

examples examples/:
	$(CC) $(CFLAGS) -o bin/examples/frogs -Lbin -I include src/examples/frogs.c -lncurses -lncknge -lm

tools tools/:
	$(CC) $(CFLAGS) -o bin/tools/bmp-view -Lbin -I include src/tools/bmp-view.c -lncurses -lncknge -lm
	$(CC) $(CFLAGS) -o bin/tools/getKeyCode -Lbin -I include src/tools/getKeyCode.c -lncurses -lncknge -lm

clean:
	rm -r bin/*
