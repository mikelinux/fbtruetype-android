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

#ifndef __CONSOLES_H
#define __CONSOLES_H

extern void init_consoles(void);
extern int current_console(void);
extern int start_console;

#endif
