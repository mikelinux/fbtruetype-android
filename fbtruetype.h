/*
 *	fbmngplay - fb console MNG player.
 *	(c) 2001-2002 by Stefan Reinauer, <stepan@suse.de>
 *  
 *	This program is based on mngplay, part of libmng, written and (C) by
 *	
 *	Ralph Giles <giles@ashlu.bc.ca>
 *
 *	This program my be redistributed under the terms of the
 *	GNU General Public Licence, version 2, or at your preference,
 *	any later version.
 */

#ifndef __FBTRUETYPE_H
#define __FBTRUETYPE_H

#define FBTRUETYPE_VERSION "0.2"

#ifndef DEFAULT_FONTNAME 
#define DEFAULT_FONTNAME "/system/fonts/DroidSans.ttf"
#endif 

extern volatile int run;
extern int verbose;
extern int buffered;
extern int dynpos;
extern int waitsignal;
extern int delta;
extern int sconly;

#endif
