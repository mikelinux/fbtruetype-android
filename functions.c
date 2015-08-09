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

#include "functions.h"

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
