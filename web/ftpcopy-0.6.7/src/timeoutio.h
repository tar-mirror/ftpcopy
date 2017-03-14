/*
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */

/* 
 * Usage: define a timeoutio function with:
 *   MKTIMEOUTREAD(60)  <- creates timeoutread60()
 *   MKTIMEOUTWRITE(60) <- creates timeoutwrite60()  
 * use them with:
 *   TIMEOUTREAD(60,fd,buf,len)
 *   TIMEOUTWRITE(60,fd,buf,len)
 */
#ifndef TIMEOUTIO_H
#define TIMEOUTIO_H

#include "taia.h"
#include "iopause.h"
#include "error.h"

#define TOFN(fn,to) timeout##fn##to

#define MKTIMEOUT(timeout,event,fn,qual) \
static int TOFN(fn,timeout)(int fdes, qual *buf, int n) \
{ \
	struct taia now, then; \
	iopause_fd x; \
	x.fd = fdes; \
	x.events = event; \
	taia_now(&now); taia_uint(&then,timeout); taia_add(&then,&now,&then); \
	do { \
		iopause(&x,1,&then,&now); \
		if (x.revents) return fn(fdes,buf,n);  \
		taia_now(&now); \
	} while (!taia_less(&then,&now)); \
	errno=error_timeout; \
	return -1; \
}

#define MKTIMEOUTREAD(to)  MKTIMEOUT(to,IOPAUSE_READ,read,void)
#define MKTIMEOUTWRITE(to) MKTIMEOUT(to,IOPAUSE_WRITE,write,const void)
#define TIMEOUTREAD(to,fd,buf,n) TOFN(read,to)((fd),(buf),(len))
#define TIMEOUTWRITE(to,fd,buf,n) TOFN(write,to)((fd),(buf),(len))
#define TIMEOUTREADFN(to) TOFN(read,to)
#define TIMEOUTWRITEFN(to) TOFN(write,to)

#endif
