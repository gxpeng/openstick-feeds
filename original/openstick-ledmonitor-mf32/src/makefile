# Makefile
#

INSTALL_PATH = /usr/local

# For GNU C compiler
CFLAGS = -Wall # -O6 -pedantic

#SHELL = /bin/sh

SHCFLAGS = -v -T # Add -T option to allow binary to be traceable

all: ledmonitor

ledmonitor: ledmonitor.c
	$(CC) $(CFLAGS) $@.c -o $@

