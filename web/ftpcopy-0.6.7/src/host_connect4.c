/* 
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 * Placed in the public domain.
 */
/* @(#) $Id: s.host_connect4.c 1.7 01/05/03 20:09:27+00:00 uwe@fjoras.ohse.de $ */
#include "stralloc.h"
#include "scan.h"
#include "ip4.h"
#include "socket.h"
#include "error.h"
#include "host_connect.h"
#include "timeoutconn.h"
#include "str.h"
#include "dns.h"
#include "byte.h"
#include "bailout.h"

#define ER(ec,en,s1,s2,s3,s4) \
	do { \
	  if (x) xbailout(ec,en,s1,s2,s3,s4); \
	  else  warning(en,s1,s2,s3,s4); \
	  return -1; \
	} while(0)
#define OOM() ER(111,error_nomem,"out of memory",0,0,0)
static int
doit(const char *host, unsigned int defaultport, unsigned long timeout,
	stralloc *remoteaddresses, int x)
{
	unsigned int l;
	char ip[4];
	unsigned long port;
	stralloc addresses=STRALLOC_INIT;

	l=ip4_scan(host,ip);
	if (l==0) {
		stralloc fqdn=STRALLOC_INIT;
		stralloc tmp=STRALLOC_INIT;
		l=str_chr(host,':');
		if (!stralloc_copyb(&tmp,host,l)) OOM();
		if (dns_ip4_qualify(&addresses,&fqdn, &tmp) == -1)
			ER(111,errno,
				"temporarily unable to figure out IP address for ",
				host,0,0);
		if (addresses.len < 4)
			ER(100,0,"no IP address for ",host,0,0);
		byte_copy(ip,4,addresses.s);
		stralloc_free(&fqdn);
		stralloc_free(&tmp);
	}
	else {
		if (!stralloc_copyb(&addresses,ip,4)) OOM();
	}
	if (host[l]==':') {
		unsigned int l2;
		l++;
		l2=scan_ulong(host+l,&port);
		if (l2==0) ER(100,0,"cannot parse ",host,0,0);
		if (host[l+l2]) ER(100,0,"cannot parse ",host,0,0);
	} else
		port=defaultport;

	for (l=0;l<addresses.len;l+=4) {
		int sock;
		sock=socket_tcp();
		if (sock==-1) 
			ER(111,errno,"cannot create socket",0,0,0);
		if (-1!=timeoutconn(sock,ip,port,timeout)) {
			if (remoteaddresses)
				if (!stralloc_copy(remoteaddresses,&addresses))
					OOM();
			stralloc_free(&addresses);
			return sock;
		}
	}
	ER(111,errno,"cannot connect socket",0,0,0);
}
int 
host_connect4(const char *host, unsigned short defport, unsigned long timeout,
	stralloc *remoteaddresses)
{
	return doit(host,defport,timeout,remoteaddresses,0);
}

int 
xhost_connect4(const char *host, unsigned short defport, unsigned long timeout,
	stralloc *remoteaddresses)
{
	return doit(host,defport,timeout,remoteaddresses,1);
}

