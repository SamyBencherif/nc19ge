
# This is the makefile for tests.

all: rebuild-main kbmToC-test-python kbmToC-test-C

rebuild-main:
	cd ../; make; cd --

kbmToC-test-python:
	../bin/tools/python/kbmToC -d tex -o py-kbm-out

kbmToC-test-C:
	# This program is currently ignoring -d param. It is hardcoded as "tex"
	../bin/tools/linux/kbmToC -d tex -o c-kbm-out
