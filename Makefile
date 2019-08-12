
CC=gcc
CFLAGS=-Wall -std=c89 -Werror# -v

AR=ar
ARFLAGS=-rs

all: library tools examples

library src/ include/:
	$(CC) $(CFLAGS) -o lib/ncknge.o -Iinclude -c src/ncknge.c
	$(AR) $(ARFLAGS) lib/libncknge.a lib/ncknge.o
	-rm lib/ncknge.o

examples examples/:
	$(CC) $(CFLAGS) -o bin/examples/frogs -Lbin -I include src/examples/frogs.c -lncurses -lncknge -lm
	$(CC) $(CFLAGS) -o bin/examples/frogs-standalone -Lbin -I include src/examples/frogs-standalone.c -lncurses -lncknge -lm
	$(CC) $(CFLAGS) -o bin/examples/cave -Lbin -I include src/examples/cave.c -lncurses -lncknge -lm
	-cp -r tex bin/examples/

tools tools/:
	$(CC) $(CFLAGS) -o bin/tools/bmp-view -Lbin -I include src/tools/bmp-view.c -lncurses -lncknge -lm
	$(CC) $(CFLAGS) -o bin/tools/getKeyCode -Lbin -I include src/tools/getKeyCode.c -lncurses -lncknge -lm

clean:
	rm -r bin/*
