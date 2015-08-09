/*
 *	fbtruetype-android
 *
 *	(c) 2015 by Michael Higham, <mhigham1986@gmail.com>
 *  
 *	This program is based on fbtruetype, written and (C) by
 *	(c) 2001-2002 by Stefan Reinauer, <stepan@suse.de>
 *
 *	This program my be redistributed under the terms of the
 *	GNU General Public Licence, version 2, or at your preference,
 *	any later version.
 */

#include <stdio.h>
#include "fbtruetype.h"
#include "messages.h"

void usage(char *name) 
{
	fprintf(stderr, "FBTrueType v%s, Copyright (C) 2015, Michael Higham <mhigham1986@gmail.com>\n", FBTRUETYPE_VERSION);
	fprintf(stderr, "\nUsage: %s [OPTION] [TEXT]\n", name);
	fprintf(stderr,
		"\nOptions:\n\n"
		"	-?, -h, --help:		Print this help.\n"
		"	-V, --version:		Show version.\n"
		"	-i, --info:		Print device display information.\n\n"
		""
		"	-z, --zygote:		Zygote mode.\n"
		"	-p, --power:		Send power key event.\n"
		"	-c, --clear		Clear the device display.\n\n"
		""
		"	-x:			X coordinate pixel [default 10]\n"
		"	-y:			Y coordinate pixel [default 10]\n"
		"	-b, --brightness:	Set display brightness [0-255] [default 170]\n"
		"	-w, --boxwidth:		Text box column size [default 65]\n"
		"	-f, --font:		Font name [.ttf file]\n"
                "	-s, --size:		Font size [default 12]\n"
		"	-t, --textcolor:	Font color [RGB Hex: FFFFFF]\n"
		"	-a, --alpha:		Alpha channel [1-100]\n\n");
}

void version(void)
{
	fprintf(stderr, 
		"fbtruetype v%s, Copyright (C) 2015, Michael Higham <mhigham1986@gmail.com>\n\n"
		"fbtruetype comes with ABSOLUTELY NO WARRANTY;\n"
		"This is free software, and you are welcome to redistribute it\n"
		"under certain conditions; Check the GPL for details.\n", FBTRUETYPE_VERSION);
}
