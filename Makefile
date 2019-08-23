
CC=gcc
CFLAGS=-Wall -std=c89 -Werror# -v

AR=ar
ARFLAGS=-rs

all: library tools examples

library src/ include/:
	$(CC) $(CFLAGS) -o lib/ncknge.o -Iinclude -c src/ncknge.c
	$(AR) $(ARFLAGS) lib/libncknge.a lib/ncknge.o
	-rm lib/ncknge.o


tools tools/:
	$(CC) $(CFLAGS) -o tools/bmp-view src/tools/bmp-view.c -Iinclude -lncknge -lncurses -lm -Llib
	$(CC) $(CFLAGS) -o tools/getKeyCode src/tools/getKeyCode.c -Iinclude -lncknge -lncurses -lm -Llib

clean:
	rm -r bin/*
