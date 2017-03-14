/* @(#) $Id: api_utimes.c 1.5 02/07/14 13:27:08+00:00 uwe@ranan.ohse.de $ */
/*
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include <time.h>
#include "api_utimes.h"
#include <sys/time.h>
/* note: this depends on a utimes replacement function */

int 
api_utimes(const char *fname,
	unsigned long at_sec, unsigned long at_usec,
	unsigned long mt_sec, unsigned long mt_usec
	)
{
	struct timeval tv[2];
	tv[0].tv_sec=at_sec;
	tv[0].tv_usec=at_usec;
	tv[1].tv_sec=mt_sec;
	tv[1].tv_usec=mt_usec;
	if (-1==utimes(fname,tv))
		return -1;
	return 0;
}
