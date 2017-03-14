/*
 * Copyright (C) 2002 Uwe Ohse, uwe@ohse.de
 * This is free software, licensed under the terms of the GNU General 
 * Public License Version 2, of which a copy is stored at:
 *    http://www.ohse.de/uwe/licenses/GPL-2
 * Later versions may or may not apply, see 
 *    http://www.ohse.de/uwe/licenses/
 * for information after a newer version has been published.
 */
#include <time.h>
#include <stdlib.h>
#include "ftpparse.h"
#include "buffer.h"
#include "stralloc.h"
#include "ftplib.h"
#include "ftpcopy.h"
#include "mdtm.h"
#include "bailout.h"
#include "error.h"
#include "utcdate2tai.h"

int
modtime_request(const char *s, struct tai *t)
{
  char *p;
  unsigned int i;
  unsigned long year,mon,day,hour,min,sec;
  year=mon=day=hour=min=sec=0;

  cmdwrite2("MDTM ",s);
  p=ccread();
  if (!p) 
    xbailout(111,errno,"failed to read MDTM answer",0,0,0);
  if (*p!='2') {
    warning(0,"got unwanted answer to `MDTM ",s,"': ",p);
    if (*p=='5' && p[1]=='0' && p[2]=='2') 
	    return -1;
    return 0;
  }
  if (!p[1]||!p[2]||p[3]!=' ') 
    goto parseerror;
  for (i=4;p[i];i++) {
    unsigned int u;
    if (p[i]<'0' || p[i]>'9') goto parseerror;
    u = (p[i] - '0');

    switch (i-4) {
    case 0: case 1: case 2: case 3:
      year *= 10;
      year += u;
      break;
    case 4: case 5:
      mon *= 10;
      mon += u;
      break;
    case 6: case 7:
      day *= 10;
      day += u;
      break;
    case 8: case 9:
      hour *= 10;
      hour += u;
      break;
    case 10: case 11:
      min *= 10;
      min += u;
      break;
    case 12: case 13:
      sec *= 10;
      sec += u;
      break;
    }
  }
  if (i!=18) {
parseerror:
    warning(0,"failed to parse ",p,0,0);
    return 0;
  }
  utcdate2tai(t,year,mon-1,day,hour,min,sec);
  return 1;
}
