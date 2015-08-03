/*
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

#include "device.h"

int fb;

void clear_zygote(void)
{
	int fb = open("/dev/graphics/fb0", O_WRONLY);
	if (fb < 0) {
		fprintf(stderr, "Error opening framebuffer on device.\n");
		exit(0);
	}

	// Write 0's all over the framebuffer, in chunks of 512 bytes.
	char* zeros = calloc(1, 512);
	ssize_t written, total = 0;
	do {
		total += written = write(fb, zeros, 512);
	} while (written == 512);
		fprintf(stderr, "Device display captured.\n");

	close(fb);
	free(zeros);
}

void clear_display(void)
{
	int fb = open("/dev/graphics/fb0", O_WRONLY);
	if (fb < 0) {
		fprintf(stderr, "Error opening framebuffer on device.\n");
		exit(0);
	}

	// Write 0's all over the framebuffer, in chunks of 512 bytes.
	char* zeros = calloc(1, 512);
	ssize_t written, total = 0;
	do {
		total += written = write(fb, zeros, 512);
	} while (written == 512);
		fprintf(stderr, "Device display cleared.\n");

	close(fb);
	free(zeros);
	exit(0);
}

void prepare_display(void)
{
	// Set the LCD power state to on
	FILE *power_set;
	if( access("/sys/class/lcd/s5p_lcd/lcd_power", F_OK ) != -1 && access("/sys/class/lcd/s5p_lcd/lcd_power", R_OK ) != -1 ) {
    		power_set=fopen("/sys/class/lcd/s5p_lcd/lcd_power", "w+");
		char on[1]="1";
		fwrite(on, sizeof(on[0]), sizeof(on)/sizeof(on[0]), power_set);
		fclose(power_set);
	} else if( access("/sys/power/state", F_OK ) != -1 && access("/sys/power/state", R_OK) != -1 ) {
    		power_set=fopen("/sys/power/state", "w+");
		char on[2]="on";
		fwrite(on, sizeof(on[0]), sizeof(on)/sizeof(on[0]), power_set);
		fclose(power_set);
	} else {
		fprintf(stderr, "Unable to set LCD power state!\n");
		exit (1);
	}

	// Set the LCD brightness to max
	FILE *brightness_set;
	if( access("/sys/class/backlight/s5p_bl/brightness", F_OK ) != -1 && access("/sys/class/backlight/s5p_bl/brightness", R_OK ) != -1 ) {
		brightness_set=fopen("/sys/class/backlight/s5p_bl/brightness", "w+");
		char max[3]="255";
		fwrite(max, sizeof(max[0]), sizeof(max)/sizeof(max[0]), brightness_set);
		fclose(brightness_set);
	} else if( access("/sys/class/leds/lcd-backlight/brightness", F_OK ) != -1 && access("/sys/class/leds/lcd-backlight/brightness", R_OK ) != -1 ) {
		brightness_set=fopen("/sys/class/leds/lcd-backlight/brightness", "w+");
		char max[3]="255";
		fwrite(max, sizeof(max[0]), sizeof(max)/sizeof(max[0]), brightness_set);
		fclose(brightness_set);
	} else {
		fprintf(stderr, "Unable to set LCD brightness!\n");
		exit (1);
	}
}

