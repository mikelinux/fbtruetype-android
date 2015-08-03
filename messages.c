/*
 *	(c) 2015 by Michael Higham, <mhigham1986@gmail.com>
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
		"	-x:			X coordinate pixel (default 10)\n"
		"	-y:			Y coordinate pixel (default 10)\n"
		"	-b, --boxwidth:		Text box column size (default 30)\n"
		"	-f, --font:		Font name (.ttf file)\n"
		"	-t, --textcolor:	Text color (RGB hex, e.g. 0xffffff)\n"
                "	-s, --size:		Font size (default 22)\n"
		"	-a, --alpha:		Alpha channel (1-100)\n"
		"	-v, --verbose:		Verbose mode\n"
		"	-V, --version:		Show version\n"
		"	-?, -h, --help:		Print this help.\n"
		"	-S, --start-console:	Output on start console only.\n"
		"	-c:			Start on specified console.\n"
		"	-d, --zygote:		Zygote is running mode.\n"
		"	-z, --clear		Clear the device display.\n\n");
}

void version(void)
{
	fprintf(stderr, 
		"fbtruetype v%s, Copyright (C) 2015, Michael Higham <mhigham1986@gmail.com>\n\n"
		"fbtruetype comes with ABSOLUTELY NO WARRANTY;\n"
		"This is free software, and you are welcome to redistribute it\n"
		"under certain conditions; Check the GPL for details.\n", FBTRUETYPE_VERSION);
}
