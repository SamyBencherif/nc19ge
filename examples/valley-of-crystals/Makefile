
# use local version
NKNGE=../..
# use system install
#NKNGE=/usr/local

# base name of binary
PROG=valley-of-crystals
# name of platform
PLAT=linux
# build date (auto)
DATE=`date +'%y.%m.%d-%H.%M.%S'`
# full name of binary
PROGNAME=$(PLAT)/$(PROG)

CC=gcc
CFLAGS=-Wall -std=c89 -Werror#

build: clean resources
	-mkdir bin
	-mkdir bin/$(PLAT)
	$(CC) $(CFLAGS) -o bin/$(PROGNAME) src/main.c -L$(NKNGE)/lib -I$(NKNGE)/include -lncurses -lncknge -lm

clean:
	-rm bin/*

resources:
	$(NKNGE)/tools/kbmToC -d src/tex -o src/resource

name:
	@echo $(PROGNAME)
