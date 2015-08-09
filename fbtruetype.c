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

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <signal.h>

#include "device.h"
#include "fbtruetype.h"
#include "messages.h"
#include "console.h"

volatile int run = 1;
int buffered = 0;
int waitsignal = 0;
int delta = 16;
int sconly=0;

unsigned int fbbytes, fbx, fby;
unsigned int fbypos=10, fbxpos=10;
unsigned int fbyposoff;
unsigned int fblinelen, alpha=100;
unsigned char *framebuffer, *font=DEFAULT_FONTNAME;
unsigned int fontcolor=0xffffff;
unsigned int fontsize=12;
int boxwidth=65;
int blen=3;
int brightness=170;
int strict_font=0;
int rendertext(char *text, char *fontname, unsigned int size, unsigned int forecol);

int strwrap(char * s, int w, char *** line_ret, int ** len_ret)
{
  int allocated; /* lines allocated */
  int lines; /* lines used */
  char ** line;
  int * len;
  int tl; /* total length of the string */
  int l; /* length of current line */
  int p; /* offset (from s) of current line */
  int close_word;
  int open_word;
  int i;
 
  if (s == NULL)
    return 0;
 
  tl = strlen(s); 
  if (tl == 0 || w <= 0)
    return 0;
 
  lines = 0;
  allocated = (tl / w) * 1.5 + 1;
  line = (char **) malloc(sizeof(char *) * allocated);
  len = (int *) malloc(sizeof(int) * allocated);
 
  if (line == NULL || len == NULL)
    return 0;
 
  p = 0; 
  while (p < tl)
  {
    if (s[p] == '\n')
    {
      l = 0;
      goto make_new_line;
    }
 
   if (p + w > tl)
    w = tl - p;
    l = w;
    close_word = 0;
 
    while (s[p + l + close_word] != '\0' && !isspace(s[p + l + close_word]))
      close_word++;
 
    while (s[p + l] != '\0' && !isspace(s[p + l]))
    {
      l--;
      open_word ++;
 
      if (open_word + close_word > w * 0.8)
      {
	l = w;
	break;
      }
    }
 
    for (i = 0; i < l; i++)
    {
      if (s[p + i] == '\n')
      {
	l = i;
	break;
      }
    }
 
  make_new_line:
    line[lines] = &s[p];
    len[lines] = l;
    lines++;
 
    if (lines >= allocated)
    {
      allocated *= 2;
      line = (char **) realloc(line, sizeof(char *) * allocated);
      len = (int *) realloc(len, sizeof(int) * allocated);
 
      if (line == NULL || len == NULL)
	return 0;
    }
 
    if (l == w)
      l--;
 
    p += l + 1;
  }
 
  line = (char **) realloc(line, sizeof(char *) * lines);
  len = (int *) realloc(len, sizeof(int) * lines);
 
  *line_ret = line;
  *len_ret = len;
 
  return lines;
}

int main(int argc, char *argv[])
{
  	char *textstr;
	char *stringraw;
  	char ** line;
  	int * len;
  	int lines;
  	int i;
	int fbdev,c,option_index;
	unsigned int alpha;
	ssize_t read(int fd, void *buf, size_t count);

	struct fb_var_screeninfo var;
	struct fb_fix_screeninfo fix;

	/* Initialize consoles */
	init_consoles();
		
	alpha = 100;
	while (1) {
		static struct option long_options[] = {
            		{"help", no_argument, 0, 'h'},
			{"version", no_argument, 0, 'V'},
			{"info", no_argument, 0, 'i'},
			{"zygote", no_argument, 0, 'z'},
			{"power", no_argument, 0, 'p'},
			{"clear", no_argument, 0, 'c'},
			{"brightness", required_argument, 0, 'b'},
			{"boxwidth", required_argument, 0, 'w'},
			{"font", required_argument, 0, 'f'},
			{"size", required_argument, 0, 's'},
			{"textcolor", required_argument, 0, 't'},
			{"alpha", required_argument, 0, 'a'},
			{0, 0, 0, 0}
		};

		c = getopt_long(argc, argv, ":x:y:h?Vizpcb:w:f:s:t:a:",
				long_options, &option_index);

		if (c == -1)
			break;

		switch (c) {
		case 'x':
			fbxpos = atoi(optarg);
			break;
		case 'y':
			fbypos = atoi(optarg);
			break;
		case '?':
		case 'h':
			usage(argv[0]);
			exit(0);
		case 'V':
			version();
			exit(0);
		case 'i':
			display_info();
			exit(0);
		case 'z':
			if (optind >= argc) {
				printf("No text\n");
				exit(0);
			}
			printf("Zygote Mode.\n");
			printf("Waiting for display to sleep...\n");
			wait_sleep();
			power_display();
			set_brightness(brightness,blen);
			wait_wake();
			clear_display();
			break;
		case 'p':
			power_key();
			exit(0);
		case 'c':
			clear_display();
			printf("Device display cleared.\n");
			exit(0);
		case 'b':
			brightness = atoi(optarg);
			if (brightness > 100 && brightness <= 255 ) {
				blen = 3;
			} else if (brightness <= 99 && brightness >= 10 ) {
				blen = 2;
			} else if (brightness <= 9 && brightness >= 0 ) {
				blen = 1;
			}
			break;
		case 'w':
			boxwidth = atoi(optarg);
			break;
		case 'f':
			strict_font=1;
			font=strdup(optarg);
			break;
		case 's':
			fontsize=strtol(optarg, NULL, 10);
			break;
		case 't':
			fontcolor=strtol(optarg, NULL, 16);
			break;
		case 'a':
			alpha = atoi(optarg);
			if (alpha > 100)
				alpha = 100;
			break;
		default:
			break;
		}
	}
	if (optind >= argc) {
		printf("No text\n");
		exit(0);
	}
	
	
	// Power on display
	power_display();

	// Set the brightness
	set_brightness(brightness,blen);

	// Initialize framebuffer
        fbdev = open("/dev/graphics/fb0", O_RDWR);
        if (fbdev < 0) {
			fprintf(stderr, "Error opening framebuffer on device.\n");
			exit(fbdev);
	}

	ioctl(fbdev, FBIOGET_VSCREENINFO, &var);
	fbbytes = var.bits_per_pixel>>3;
	fbx=var.xres; 
	fby=var.yres;
	ioctl(fbdev, FBIOGET_FSCREENINFO, &fix);
	fblinelen = fix.line_length;
	fbyposoff = fbypos;

	stringraw = argv[optind];
	lines = strwrap(stringraw, boxwidth, &line, &len);
	  for (i = 0; i < lines; i++)
	  {
	    if (i > 0)
	    {
	    fbypos += fontsize;
	    }
	    if (fbypos + fontsize >= fby - fbyposoff)
    	    {
    	      exit(0);
    	    }
	    strncpy(textstr, line[i], len[i]);
	    textstr[len[i]] = '\0';
	     	//printf("%4d |%-*s|\n", len[i], boxwidth, argv[optind]);
	    framebuffer = mmap(NULL,  fblinelen* fby ,
		 PROT_WRITE | PROT_READ, MAP_SHARED, fbdev, var.yoffset * fblinelen);
	    rendertext (("%s", len[i], boxwidth, textstr), font, fontsize, fontcolor);
	  }

	free(line);
	free(len);
	return 0;
}
