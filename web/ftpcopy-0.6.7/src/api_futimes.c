/*
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include <time.h>
#include <sys/time.h>
#include <utime.h>
#include "auto-have_futimes.h"
#include "api_futimes.h"
#include "api_utimes.h"

int 
api_futimes_1(int fd, 
	unsigned long at_sec, unsigned long at_usec,
	unsigned long mt_sec, unsigned long mt_usec
	)
{
#ifdef HAVE_FUTIMES
	struct timeval tv[2];
	tv[0].tv_sec=at_sec;
	tv[0].tv_usec=at_usec;
	tv[1].tv_sec=mt_sec;
	tv[1].tv_usec=mt_usec;
	if (-1==futimes(fd,tv))
		return -1;
#endif
(void) fd;
(void) mt_sec;
(void) mt_usec;
(void) at_sec;
(void) at_usec;
	return 0;
}

int 
api_futimes_2(const char *fname, 
	unsigned long at_sec, unsigned long at_usec,
	unsigned long mt_sec, unsigned long mt_usec
	)
{
#ifndef HAVE_FUTIMES
	return api_utimes(fname,at_sec,at_usec, mt_sec,mt_usec);
#else
(void) fname;
(void) mt_sec;
(void) mt_usec;
(void) at_sec;
(void) at_usec;
	return 0;
#endif
}
