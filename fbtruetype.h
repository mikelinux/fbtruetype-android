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

#ifndef __FBTRUETYPE_H
#define __FBTRUETYPE_H

#define FBTRUETYPE_VERSION "0.40"

#ifndef DEFAULT_FONTNAME 
#define DEFAULT_FONTNAME "/system/fonts/DroidSansMono.ttf"
#endif 

extern volatile int run;
extern int buffered;
extern int dynpos;
extern int waitsignal;
extern int delta;
extern int sconly;

#endif
