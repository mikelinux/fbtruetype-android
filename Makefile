# Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

ARCH     = arm
SHELL    = /bin/sh
CC       = arm-linux-gnueabi-gcc
LIBDIR   = ./libs

PROGRAM = fbtruetype
OBJECTS  = fbtruetype.o functions.o messages.o device.o console.o ttf.o droidsansmono.o

LDFLAGS  += -L$(LIBDIR)
LIBS    = $(LIBDIR)/libfreetype.a $(LIBDIR)/libz.a -lm

CFLAGS   += -I./include/freetype2
COMPILE  = $(CC) $(CFLAGS)
LINKS    = $(CC) $(CFLAGS) $(LDFLAGS) -static -o $@

all: $(PROGRAM)

clean:
	-rm -f fbtruetype *.o core

fbtruetype: $(OBJECTS)
	@rm -f fbtruetype
	$(LINKS) $(LDFLAGS) $(OBJECTS) $(LIBS)
