/*
 * Copyright (C) 2002 Uwe Ohse, uwe@ohse.de
 * This is free software, licensed under the terms of the GNU General 
 * Public License Version 2, of which a copy is stored at:
 *    http://www.ohse.de/uwe/licenses/GPL-2
 * Later versions may or may not apply, see 
 *    http://www.ohse.de/uwe/licenses/
 * for information after a newer version has been published.
 */
#include "buffer.h"
#include "attributes.h"
#include "stralloc.h"
#include "str.h"
#include "ftplib.h"
#include "bailout.h"
#include "byte.h"
#include "ftpcopy.h"
#include "error.h"
#include "timeoutio.h"
#include "host_connect.h"
#include "readwrite.h"
#include "iopause.h"
#include "close.h"
#include "mysleep.h"
#include "ip6.h"
#include "socket.h"
#include "socket_if.h"
#include "scan.h"

static stralloc io_i_mem;
static stralloc io_o_mem;
unsigned long o_data_connect_retries;
int o_eat_leading_spaces;

MKTIMEOUTREAD(o_timeout)
MKTIMEOUTWRITE(o_timeout)
static void die_remoteread(void) attribute_noreturn;
static void die_commandwrite(void) attribute_noreturn;
static void die_remoteeof(void) attribute_noreturn;
static void die_logwrite(void) attribute_noreturn;

#ifdef HAVE_IPV6
static void die_bad_epsv(const char *s) attribute_noreturn;
static void die_bad_epsv(const char *s)
{ xbailout(111,0,"bad EPSV 2 answer: ",s,0,0); }
#endif

static void die_remoteread(void)
{ xbailout(111,errno,"failed to read from remote",0,0,0);}
static void die_commandwrite(void)
{ xbailout(111,errno,"failed to send command",0,0,0);}
static void die_remoteeof(void)
{ xbailout(111,errno,"connection closed by remote host",0,0,0);}
static void die_logwrite(void) 
{xbailout(111,errno,"failed to write log",0,0,0);}


char *
ccread(void)
{
	static stralloc sa=STRALLOC_INIT;
	switch(ftp_cc_read(&io_i,&sa)) {
	case  0: errno=0; /* FALL THROUGH */
	case -1: return 0;
	}
	if (!*sa.s) return 0;
	return sa.s;
}
char *
ccread_oneline(void)
{
	static stralloc sa=STRALLOC_INIT;
	switch(ftp_cc_read_oneline(&io_i,&sa)) {
	case  0: errno=0; /* FALL THROUGH */
	case -1: return 0;
	}
	if (!*sa.s) return 0;
	return sa.s;
}
void
cmdwrite2(const char *s1, const unsigned char *s2)
{
	if (-1==ftp_cc_write_cmd_ss(&io_o,s1,s2))
		die_commandwrite();
}
void x2(const char *where)
{
	char *p;
	p=ccread();
	if (!p) {
	  if (!errno)  die_remoteeof();
	  die_remoteread();
	}
	if (*p != '2') xbailout(111,0,"received unwanted answer to ",where,": ",p);
}
void sx2(const char *what)
{
	cmdwrite1(what);
	x2(what);
}
void
cmdwrite1(const char *s1)
{
	if (-1==ftp_cc_write_cmd_s(&io_o,s1)) 
		die_commandwrite();
}
#define LOGSTR(x) if (-1==buffer_puts(buffer_1,(x))) die_logwrite();
#define LOGMEM(x,y) if (-1==buffer_put(buffer_1,(x),(y))) die_logwrite();
#define LOGFLUSH() if (-1==buffer_flush(buffer_1)) die_logwrite();

void do_log1(const char *s1) { LOGSTR(s1); LOGFLUSH(); }
void do_log2(const char *s1, const char *s2)
	{ LOGSTR(s1); LOGSTR(s2); LOGFLUSH(); }
void do_log3(const char *s1, const char *s2, const char *s3)
	{ LOGSTR(s1); LOGSTR(s2); LOGSTR(s3); LOGFLUSH(); }
void do_log4(const char *s1, const char *s2, const char *s3, const char *s4)
	{ LOGSTR(s1); LOGSTR(s2); LOGSTR(s3); LOGSTR(s4); LOGFLUSH(); }
void do_logmem(const char *s1,unsigned int l) { LOGMEM(s1,l); LOGFLUSH(); }

int
do_pasv(void)
{
  static stralloc meld=STRALLOC_INIT;
  int x;
#ifdef HAVE_IPV6
  static int family=-1;
  if (-1==family) {
    family=socket_family(io_i.fd);
    if (-1==family)
      xbailout(111,errno,"failed to inquire socket family",0,0,0);
    if (6==family)
      sx2("EPSV ALL");
  }
  if (6==family) {
    unsigned int i;
    unsigned int j;
    unsigned char c;
    unsigned long port;
    char *p;
    char ip[16];
    uint16 cport;
    uint32 scope_id;
    char ipf[IP6_FMT];
    static stralloc sa;
    static stralloc ifname;
    cmdwrite1("EPSV 2"); /* 2 == IPV6, how smart! */
    p=ccread();
    if (!p) {
      if (!errno)  die_remoteeof();
      die_remoteread();
    }
    i=str_len(p)-1;
    if (p[i]!=')') die_bad_epsv(p);
    while (i && p[i]!='(') i--;
    if (p[i]!='(') die_bad_epsv(p);
    c=p[++i];
    if (p[++i]!=c) die_bad_epsv(p);
    if (p[++i]!=c) die_bad_epsv(p);
    ++i;
    j=scan_ulong(p+i,&port);
    if (!j||p[i+j]!=c) die_bad_epsv(p);
    i+=j;
    if (p[++i]!=')') die_bad_epsv(p);
    if (p[++i]) die_bad_epsv(p);
    if (-1==socket_remote6(io_i.fd,ip,&cport,&scope_id))
      xbailout(111,errno,"failed to inquire remote address on control socket",
	0,0,0);
    if (!stralloc_copyb(&sa,ipf,ip6_fmt(ipf,ip))) oom();
    if (scope_id) {
      if (-1==socket_getifname(&ifname,scope_id))
	xbailout(111,errno,"failed to inquire socket interface",0,0,0);
      if (!stralloc_cats(&sa,"%")) oom();
      if (!stralloc_cats(&sa,ifname.s)) oom();
    }
    if (!stralloc_0(&sa)) oom();
    return xhost_connect64(sa.s,port,o_timeout,0);
  }
#endif

  x=ftp_cc_pasv(&io_i,&io_o,o_timeout,&pasv_response_ips,&meld,
    o_data_connect_retries);
  if (!stralloc_0(&meld)) oom();
  switch(x) {
  case 0: die_remoteeof();
  case -1: die_remoteread();
  case -2: xbailout(111,0,"cannot parse PASV answer",
    meld.len>1 ? ": ":0,meld.len>1?meld.s:0,0);
  case -3: xbailout(111,0,"illegal redirect by FTP server",
    meld.len>1 ? " in ":0, meld.len>1?meld.s:0, 0);
  }
  return x;
}
int
connect_auth (const char *host, const char *o_user, 
	const char *o_pass, const char *o_acct, int tries)
{
	if (!stralloc_ready(&io_i_mem,BUFFER_INSIZE)) oom();
	if (!stralloc_ready(&io_o_mem,BUFFER_OUTSIZE)) oom();
	if (!o_login_sleep)
		o_login_sleep=1;

	while (1) {
		int need_auth = 1;
		int need_acct = 0;
		unsigned int i;
		char *p;
		int sock;
		if (!tries) 
			xbailout(111,0,"failed to connect or log in",0,0,0);
		tries--;
		if (!tries)
			sock=xhost_connect64(host,21,o_timeout,&remoteip);
		else
			sock=host_connect64(host,21,o_timeout,&remoteip);
		if (sock==-1)
			goto dosleep1;

		buffer_init(&io_i,(buffer_op)TIMEOUTREADFN(o_timeout),sock,
		io_i_mem.s,BUFFER_INSIZE);
		buffer_init(&io_o,(buffer_op)TIMEOUTWRITEFN(o_timeout),sock,
		io_o_mem.s,BUFFER_OUTSIZE);

		p = ccread ();
		if (!p) {
			if (tries) goto dosleep;
			if (!errno) 
				die_remoteeof();
			die_remoteread();
		}
		if (o_loglevel > 2)
			do_log2 (p, "\n");
		if (!str_start (p, "220 ")) {
			if (!tries) 
				xbailout (111,0, "received unexpected greeting message: ", 
					p, 0, 0);
			goto dosleep;
		}
		if (!o_user || !*o_user) 
			need_auth=0;
		if (str_start(p,"220 Features:")) {
			char *q;
			for (q = p; *q; q++) {
				if (*q == ' ' && q[1] == 'a')
					break;
			}
			if (*q)
				if (str_equal (o_user, "anonymous")
					|| str_equal (o_user, "ftp"))
					need_auth = 0;
		}

		if (need_auth) {
			cmdwrite2 ("USER ", o_user);
			p = ccread ();
			if (!p) {
				if (tries) goto dosleep;
				if (!errno) 
					die_remoteeof();
				die_remoteread();
			}
			if (o_loglevel > 2)
				do_log2 (p, "\n");
			if (*p == '5') {
				if (tries) goto dosleep;
				xbailout (111,0, "received unwanted USER response: ", p, 0, 0);
			}
			if (*p == '2')
				goto finish;
			if (o_pass && *o_pass) {
				cmdwrite2 ("PASS ", o_pass);
				p = ccread ();
				if (!p) {
					if (tries) goto dosleep;
					if (!errno)
						die_remoteeof();
					die_remoteread();
				}
				if (o_loglevel > 2)
					do_log2 (p, "\n");
				if (str_start(p,"332"))
					need_acct=1;
				else if (*p != '2') {
					if (!tries) 
						xbailout (111,0, "remote host rejected password: ", 
							p, 0, 0);
					goto dosleep;
				}
			} else
				xbailout(111,0,"remote host asked for password.",0,0,0);
			if (need_acct) {
				if (!o_acct)
					xbailout(111,0,"remote host asked for ACCT.",0,0,0);
				cmdwrite2 ("ACCT ", o_acct);
				p = ccread ();
				if (!p) {
					if (tries) goto dosleep;
					if (!errno)
						die_remoteeof();
					die_remoteread();
				}
				if (o_loglevel > 2)
					do_log2 (p, "\n");
				if (*p != '2') {
					if (!tries) 
						xbailout(111,0,"remote host rejected account: ",p,0,0);
					goto dosleep;
				}
			}
		}
	      finish:
		/* add to pasv_response_ips */
		for (i=0;i<remoteip.len;i+=16) {
		  if (ip6_isv4mapped(remoteip.s+i)) {
		    if (!stralloc_catb(&pasv_response_ips,
		      remoteip.s+i+sizeof(V4mappedprefix),
		      16-sizeof(V4mappedprefix))) oom();
		  }
		}
		return sock;
	  dosleep:
		close(sock);
	  dosleep1:
	  	mysleep(o_login_sleep);
	}
}
