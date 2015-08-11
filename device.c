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
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <regex.h>
#include <linux/input.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <linux/vt.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "device.h"

int fb;

char *regexp (char *string, char *patrn, int *begin, int *end) {     
        int i, w=0, len;                  
        char *word = NULL;
        regex_t rgT;
        regmatch_t match;
        regcomp(&rgT,patrn,REG_EXTENDED);
        if ((regexec(&rgT,string,1,&match,0)) == 0) {
                *begin = (int)match.rm_so;
                *end = (int)match.rm_eo;
                len = *end-*begin;
                word=malloc(len+1);
                for (i=*begin; i<*end; i++) {
                        word[w] = string[i];
                        w++; }
                word[w]=0;
        }
        regfree(&rgT);
        return word;
}

void clear_display(void)
{
	int fb = open("/dev/graphics/fb0", O_WRONLY);
	if (fb < 0) {
		printf("Error opening framebuffer on device.\n");
		exit(0);
	}

	// Write 0's all over the framebuffer, in chunks of 512 bytes.
	char* zeros = calloc(1, 512);
	ssize_t written, total = 0;
	do {
		total += written = write(fb, zeros, 512);
	} while (written == 512);

	close(fb);
	free(zeros);
}

void power_key(void)
{
	// Send short press power key
	FILE *devfile;
    	int fd;
	int b,e;
	long s = 0;
	ssize_t ret;
	char *devstr;
	char *matchblock;
	char *eventres;
	char eventstr[20];
	struct input_event event1;
	struct input_event event2;
	struct input_event event3;
	struct input_event event4;

	if((devfile = fopen("/proc/bus/input/devices", "rb")) == NULL) {
		printf("Error reading devices file!\n");
		exit(0);
	} else {
		devfile = fopen("/proc/bus/input/devices", "rb");
			if ( devfile != NULL ) {
				while (getc(devfile) != EOF) {
					s++;
				}
				rewind(devfile);
				devstr = malloc(s);
				if ( devstr != NULL ) {
	  				fread(devstr, s, 1, devfile);
	      				fclose(devfile);
					devfile = NULL;
					//printf("%s\n",devstr);
 
	  				if((matchblock = regexp(devstr,"event[0-9]*[A-z0-9 ]*(\n)B:[ ]*PROP=[A-z0-9]*(\n)B:[ ]*EV=[A-z0-9]*(\n)B:[ ]*KEY=[0-9 ]*1c0[0-9]00 ",&b,&e)) != NULL) {
						matchblock = regexp(devstr,"event[0-9]*[A-z0-9 ]*(\n)B:[ ]*PROP=[A-z0-9]*(\n)B:[ ]*EV=[A-z0-9]*(\n)B:[ ]*KEY=[0-9 ]*1c0[0-9]00 ",&b,&e);
					} else if((matchblock = regexp(devstr,"event[0-9]*[A-z0-9 ]*(\n)B:[ ]*EV=[A-z0-9]*(\n)B:[ ]*KEY=[0-9 ]*1c0[0-9]00 ",&b,&e)) != NULL) {
						matchblock = regexp(devstr,"event[0-9]*[A-z0-9 ]*(\n)B:[ ]*EV=[A-z0-9]*(\n)B:[ ]*KEY=[0-9 ]*1c0[0-9]00 ",&b,&e);
					} else {
						printf("Error finding input device!\n");
						exit(0);
	  				}

	  				if((eventres = regexp(matchblock,"event[0-9]*",&b,&e)) != NULL) {
						eventres = regexp(matchblock,"event[0-9]*",&b,&e);
						snprintf(eventstr, sizeof eventstr, "%s%s", "/dev/input/", eventres);
					} else {
						printf("Error finding input event number!\n");
						exit(0);
	  				}
	  					free(devstr);
			}
  		}
		if (devfile != NULL) {
			fclose(devfile);
		}
	}

	//printf("Input device = %s\n", eventstr);

	fd = open(eventstr, O_RDWR);
	if(fd < 0) {
	    printf("Error reading input device!\n");
	    exit(0);
	}

	memset(&event1, 0, sizeof(event1));
	event1.type = 1;
	event1.code = 116;
	event1.value = 1;
	ret = write(fd, &event1, sizeof(event1));
	if(ret < (ssize_t) sizeof(event1)) {
	    printf("Error writing to event!\n");
	    exit(0);
	}

	memset(&event2, 0, sizeof(event2));
	event2.type = 0;
	event2.code = 0;
	event2.value = 0;
	ret = write(fd, &event2, sizeof(event2));
	if(ret < (ssize_t) sizeof(event2)) {
	    printf("Error writing to event!\n");
	    exit(0);
	}

	memset(&event3, 0, sizeof(event3));
	event3.type = 1;
	event3.code = 116;
	event3.value = 0;
	ret = write(fd, &event3, sizeof(event3));
	if(ret < (ssize_t) sizeof(event3)) {
	    printf("Error writing to event!\n");
	    exit(0);
	}

	memset(&event4, 0, sizeof(event4));
	event4.type = 0;
	event4.code = 0;
	event4.value = 0;
	ret = write(fd, &event4, sizeof(event4));
	if(ret < (ssize_t) sizeof(event4)) {
	    printf("Error writing to event!\n");
	    exit(0);
	}
}

void power_status(void)
{
	char power_status[3];
	FILE *pwr_stat;

	// Get the display power state
	if( access("/sys/power/wait_for_fb_status", F_OK ) != -1 && access("/sys/power/wait_for_fb_status", R_OK) != -1 ) {
		pwr_stat = fopen("/sys/power/wait_for_fb_status","r");
		fscanf(pwr_stat, "%s", power_status);	
		fclose(pwr_stat);

	} else {
		printf("Unable to get display power status!\n");
		fclose(pwr_stat);
		exit(0);
	}
}

void display_info(void)
{
	int *xres;
	int *yres;
	char power_status[3];
	static struct fb_var_screeninfo var;
	FILE *pwr_stat;

	// Get the display power status
	pwr_stat = fopen("/sys/power/wait_for_fb_status","r");

	if( access("/sys/power/wait_for_fb_status", F_OK ) != -1 && access("/sys/power/wait_for_fb_status", R_OK) != -1 ) {
		fscanf(pwr_stat, "%s", power_status);	
		fclose(pwr_stat);
	} else {
		printf("Unable to get display power status!\n");
		fclose(pwr_stat);
		exit(0);
	}

	// Get display resolution information
	fb = open("/dev/graphics/fb0", O_RDWR);
	if (fb == -1) {
		printf("Error opening display!\n");
		exit(0);
	}

	if (ioctl(fb, FBIOGET_VSCREENINFO, &var) < 0) {
		printf("Error probing display information!\n");
		close(fb);
		exit(0);
	}
	close(fb);

	printf("------------------------------\n");
	printf("Display:\tfb0\n");
	printf("------------------------------\n");
	printf("Resolution:\t%dx%d\n", var.xres, var.yres);
	printf("BPP:\t\t%d\n", var.bits_per_pixel);
	printf("Power state:\t%s\n", power_status);
	printf("------------------------------\n");
}

void power_display(void)
{
	// Set the display power state to on
	FILE *power_set;
	if( access("/sys/power/state", F_OK ) != -1 && access("/sys/power/state", R_OK) != -1 ) {
    		power_set=fopen("/sys/power/state", "w+");
		char on[2]="on";
		fwrite(on, sizeof(on[0]), sizeof(on)/sizeof(on[0]), power_set);
		fclose(power_set);
	} else {
		fprintf(stderr, "Unable to set display power state!\n");
		exit(1);
	}
}

void set_brightness(int brightness, int blen)
{
	char max[(blen)];
	sprintf(max, "%d", brightness);

	// Set the display brightness
	FILE *brightness_set;
	if( access("/sys/class/backlight/panel/brightness", F_OK ) != -1 && access("/sys/class/backlight/panel/brightness", R_OK ) != -1 ) {
		brightness_set=fopen("/sys/class/backlight/panel/brightness", "w+");
		fwrite(max, sizeof(max[0]), sizeof(max)/sizeof(max[0]), brightness_set);
		fclose(brightness_set);
	} else if( access("/sys/class/leds/lcd-backlight/brightness", F_OK ) != -1 && access("/sys/class/leds/lcd-backlight/brightness", R_OK ) != -1 ) {
		brightness_set=fopen("/sys/class/leds/lcd-backlight/brightness", "w+");
		fwrite(max, sizeof(max[0]), sizeof(max)/sizeof(max[0]), brightness_set);
		fclose(brightness_set);
	} else {
		printf("Unable to set display brightness!\n");
		exit(1);
	}
}

void wait_sleep()
{
   char sleep_status[8];
   FILE *sleep_stat;

   // Wait for the display to sleep
   if (access("/sys/power/wait_for_fb_sleep", F_OK ) != -1 && access("/sys/power/wait_for_fb_sleep", R_OK) != -1) {
   	sleep_stat = fopen("/sys/power/wait_for_fb_sleep","r");
   	fscanf(sleep_stat, "%s", sleep_status);
   	fclose(sleep_stat);

	// Loop to check sleep status
   	while (strcmp(sleep_status, "sleeping") != 0) {
		sleep_stat = fopen("/sys/power/wait_for_fb_sleep","r");
   		fscanf(sleep_stat, "%s", sleep_status);
     		fclose(sleep_stat);
   	}
   } else {
	printf("Unable to get sleep status!\n");
   }
}

void wait_wake()
{
   char wake_status[5];
   FILE *wake_stat;
 
   // Wait for the display to wake up
   if (access("/sys/power/wait_for_fb_wake", F_OK ) != -1 && access("/sys/power/wait_for_fb_wake", R_OK) != -1) {
	wake_stat = fopen("/sys/power/wait_for_fb_wake","r");
   	fscanf(wake_stat, "%s", wake_status);
   	fclose(wake_stat);

	// Loop to check wake status
   	while (strcmp(wake_status, "awake") != 0) {
		wake_stat = fopen("/sys/power/wait_for_fb_wake","r");
   		fscanf(wake_stat, "%s", wake_status);
		fclose(wake_stat);
   	}

	// Pause to let display initialize
   	sleep(1.5);

   } else {
	printf("Unable to get wake status!\n");
   }
}
