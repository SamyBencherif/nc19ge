
# use local version
ifndef NKNGE
NKNGE=../..
endif
# use system install
#NKNGE=/usr/local

# base name of binary
PROG=valley-of-crystals

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

CFLAGS=-Wall -std=c89 -Werror#

debug: clean resources
	$(CC) $(CFLAGS) -Ddev -o bin/$(PROGNAME) src/main.c -L$(NKNGE)/lib/$(PLAT) -I$(NKNGE)/include -lncknge -lncurses -lm

release: clean resources
	$(CC) $(CFLAGS) -o bin/$(PROGNAME) src/main.c -L$(NKNGE)/lib/$(PLAT) -I$(NKNGE)/include -lncknge -lncurses -lm

clean:
	-rm bin/$(PLAT)/*
	-mkdir bin
	-mkdir bin/$(PLAT)

resources:
	$(NKNGE)/tools/kbmToC -d src/tex -o src/resource

name:
	@echo $(PROGNAME)

