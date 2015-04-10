/*
 *	fbmngplay - framebuffer console MNG player.
 *	(c) 2001-2002 by Stefan Reinauer, <stepan@suse.de>
 *   
 *	This program is based on mngplay, part of libmng, written and (C) by
 *	Ralph Giles <giles@ashlu.bc.ca>
 *
 *	This program my be redistributed under the terms of the
 *	GNU General Public Licence, version 2, or at your preference,
 *	any later version.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/kd.h>
#include <linux/vt.h>
#include <sys/ioctl.h>

#include "console.h"

int start_console = 0;
int fd;

int current_console(void)
{
	int  result=0;
	char twelve=12;

	result = ioctl(fd, TIOCLINUX, &twelve);

	return result;
}

void init_consoles(void)
{

	/* Check for ADB virtual terminal */
	fd=open("/dev/tty", O_RDWR|O_NDELAY);
	if (fd<0) {
		fd=open("/dev/tty0", O_RDWR|O_NDELAY);
		if (fd<0) {
			fprintf(stderr, "Could not open virtual terminal.\n");
			exit (1);
		}
	}

}


