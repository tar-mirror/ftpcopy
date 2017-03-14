/* 
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 * Placed in the public domain.
 */
#include "stralloc.h"
#include "scan.h"
#include "ip6.h"
#include "ip4.h"
#include "socket.h"
#include "error.h"
#include "host_connect.h"
#include "timeoutconn.h"
#include "str.h"
#include "dns.h"
#include "byte.h"
#include "bailout.h"
#include "close.h"
#include "socket_if.h"

#define ER(ec,en,s1,s2,s3,s4) \
  do { \
    if (x) xbailout(ec,en,s1,s2,s3,s4); \
    else  warning(en,s1,s2,s3,s4); \
    return -1; \
  } while(0)
#define OOM() ER(111,0,"out of memory",0,0,0)

/*
 * this is much more complicated than i'd like it, mainly due to the
 * fact that ipv4-in-v6 mapped addresses don't work under KAME / *BSD.
 * I fail to see a reason this this.
 */
static int 
doit(const char *host, unsigned int defaultport, 
  unsigned long timeout, stralloc *remoteaddresses,
  int x)
{
  unsigned int l;
  char ip6[16];
  char ip4[4];
  unsigned long port;
  stralloc addresses=STRALLOC_INIT;
  static int ipv6_error=0;
  static int ipv6_supported=-1;
  uint32 scope=0;

  if (-1==ipv6_supported) {
    if (socket_flag_noipv6)
      ipv6_supported=0;
  }
  if (-1==ipv6_supported) {
    int sock;
    sock=socket_tcp6();
    if (-1==sock) {
      ipv6_supported=0;
      ipv6_error=errno;
    } else {
      ipv6_supported=1;
      close(sock);
    }
  }

  l=ip6_scan(host,ip6);
  if (l) {
    if (host[l]=='%') {
      l++;
      scope=socket_getifidx(host+l);
      if (!scope)
	ER(100,errno, 
	  "cannot find interface ",host+l,0,0);
      l+=str_len(host+l);
    }
    if (!stralloc_copyb(&addresses,ip6,16)) OOM();
  } else {
    l=ip4_scan(host,ip4);
    if (l) {
      if (!stralloc_copyb(&addresses,V4mappedprefix,12)) OOM();
      if (!stralloc_catb(&addresses,ip4,4)) OOM();
    } else {
      stralloc fqdn=STRALLOC_INIT;
      stralloc tmp=STRALLOC_INIT;
      unsigned int m;
      m=str_chr(host,'%');
      l=str_chr(host,':');
      if (m<l) 
	l=m;
      if (!stralloc_copyb(&tmp,host,l)) OOM();
      if (dns_ip64_qualify(&addresses,&fqdn, &tmp) == -1)
	ER(111,errno, 
	  "temporarily unable to figure out IP address for ",
	    host,0,0);
      if (addresses.len < 16)
	      ER(100,0,"no IP address for ",host,0,0);
      byte_copy(ip6,16,addresses.s);
      stralloc_free(&fqdn);
      stralloc_free(&tmp);
      if ('%'==host[l]) {
	stralloc sa=STRALLOC_INIT;
	l++;
	m=str_chr(host+l,':');
	if (!stralloc_copyb(&sa,host+l,m)) OOM();
	if (!stralloc_0(&sa)) OOM();
	scope=socket_getifidx(sa.s);
	if (!scope)
	  ER(100,errno, 
	    "cannot find interface ",host+l,0,0);
	l+=m;
	stralloc_free(&sa);
      }
    }
  }
  if (host[l]==':') {
    unsigned int l2;
    l++;
    l2=scan_ulong(host+l,&port);
    if (l2==0) ER(100,0,"cannot parse ",host,0,0);
    if (host[l+l2]) ER(100,0,"cannot parse ",host,0,0);
  } else
    port=defaultport;

  errno=error_afnosupport;
  for (l=0;l<addresses.len;l+=16) {
    int sock;
    int proto=0;
    if (ipv6_supported) {
      if (!ip6_isv4mapped(addresses.s+l)) {
	sock=socket_tcp6();
	proto=6;
      } else {
	if (socket_flag_noipv4) 
	  continue;
	sock=socket_tcp();
	proto=4;
      }
    } else {
      if (!ip6_isv4mapped(addresses.s+l)) {
	continue;
      }
      if (socket_flag_noipv4)
	continue;
      sock=socket_tcp();
      proto=4;
    }
    if (sock==-1) 
      ER(111,errno,"failed to create socket",0,0,0);
    if (proto==4) {
      if (-1==timeoutconn(sock,addresses.s+l+12,port,timeout)) 
	continue;
    } else {
      if (-1==timeoutconn6(sock,addresses.s+l,port,timeout,scope)) 
	continue;
    }
    if (remoteaddresses)
      if (!stralloc_copy(remoteaddresses,&addresses)) OOM();
    stralloc_free(&addresses);
    return sock;
  }
  ER(111,errno,"cannot connect socket",0,0,0);
}

int host_connect64(const char *host, unsigned int defaultport, 
  unsigned long timeout, stralloc *remoteaddresses)
{
  return doit(host,defaultport,timeout,remoteaddresses,0);
}
int xhost_connect64(const char *host, unsigned int defaultport, 
  unsigned long timeout, stralloc *remoteaddresses)
{
  return doit(host,defaultport,timeout,remoteaddresses,1);
}
