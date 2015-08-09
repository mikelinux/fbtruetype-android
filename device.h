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

#ifndef __DEVICE_H
#define __DEVICE_H

extern void clear_display(void);
extern void power_key(void);
extern void power_status(void);
extern void power_display(void);
extern void set_brightness(int brightness, int blen);
extern void wait_sleep(void);
extern void wait_wake(void);

#endif
