
# use local version
ifndef NCKNGE
NCKNGE=../..
endif
# use system install
#NCKNGE=/usr/local

# base name of binary
PROG=school-proj

# name of platform
ifndef PLAT
PLAT="$(shell uname | tr A-Z a-z)"
endif

# build date (auto)
DATE=`date +'%y.%m.%d-%H.%M.%S'`

# full name of binary
PROGNAME=$(PLAT)/$(PROG)

ifndef CC
CC=gcc
endif

CFLAGS=-Wall -std=c89 -Werror# -v

AR=ar
ARFLAGS=-rs

all: library tools

library src/ include/:

	$(CC) $(CFLAGS) -o lib/$(PLAT)/ncknge.o -Iinclude -c src/ncknge.c
	$(AR) $(ARFLAGS) lib/$(PLAT)/libncknge.a lib/$(PLAT)/ncknge.o
	-rm lib/$(PLAT)/ncknge.o


tools tools/:
	$(CC) $(CFLAGS) -o tools/$(PLAT)/bmp-view src/tools/bmp-view.c -Iinclude -lncknge -lncurses -lm -Llib
	$(CC) $(CFLAGS) -o tools/$(PLAT)/getKeyCode src/tools/getKeyCode.c -Iinclude -lncknge -lncurses -lm -Llib

