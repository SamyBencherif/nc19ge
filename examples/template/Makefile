
# use local version
ifndef NCKNGE
NCKNGE=../..
endif
# use system install
#NCKNGE=/usr/local

# base name of binary
PROG=program

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

build: clean resources
	$(CC) $(CFLAGS) -o bin/$(PROGNAME) src/main.c -lncknge -L$(NCKNGE)/lib/$(PLAT) -I$(NCKNGE)/include -lncurses -lm

library:
	-cd $(NCKNGE); make; cd -

clean:
	-rm bin/$(PLAT)/*

resources:
	-$(NCKNGE)/tools/kbmToC -d src/tex -o src/resource

name:
	@echo $(PROGNAME)

