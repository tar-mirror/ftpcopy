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
#include "stralloc.h"
#include "ip4.h"
#include "scan.h"
#include "getln.h"
#include "ftplib.h"
#include "host_connect.h"
#include "str.h"
#include "fmt.h"
#include "byte.h"

static int
ftp_cc_write_escaped(buffer *io, const unsigned char *s)
{
	while (*s) {
		if (*s==255)
			if (-1==buffer_put(io,s,1)) return -1;
		if (-1==buffer_put(io,s++,1)) return -1;
	}
	return 0;
}

int
ftp_cc_write_cmd_s(buffer *io, const unsigned char *s1)
{
	if (ftp_cc_write_escaped(io,s1)) return -1;
	if (-1==buffer_puts(io,"\r\n")) return -1;
	return buffer_flush(io);
}

int
ftp_cc_write_cmd_ss(buffer *io, const unsigned char *s1, 
	const unsigned char *s2)
{
	if (-1==ftp_cc_write_escaped(io,s1)) return -1;
	if (-1==ftp_cc_write_escaped(io,s2)) return -1;
	if (-1==buffer_puts(io,"\r\n")) return -1;
	return buffer_flush(io);
}

int
ftp_cc_read_oneline(buffer *io, stralloc *ret) 
{
	char *p;
	unsigned char *q,*w,*e;
	unsigned int l;
	int gotlf;

	if (-1==getln(io,ret,&gotlf,'\n')) return -1;
	if (ret->len==0) return 0;

	p=ret->s;
	l=ret->len;
	for (q=p,e=p+l,w=p;q!=e;) {
		if (*q==255 && q!=e-1)
			q++;
		*w++=*q++;
	}

	l=w-(unsigned char *)p;
	if (l<2 || p[l-1]!='\n') return 0;
	l--; if (p[l-1]=='\r') l--;
	p[l]=0;
	ret->len=l+1;

	return 1;
}

/* should probably handle escapes more clever. */
int
ftp_cc_read(buffer *io, stralloc *ret) 
{
	int multiline=0;
	ret->len=0;
	if (!stralloc_0(ret)) return -1;
	while (1) {
		int x;
		char *p;
		x=ftp_cc_read_oneline(io, ret);
		if (!x)
		  return 0;
		p=ret->s;
		if (ret->len>=4 
			&& (p[0]>='0' && p[0]<='9')
			&& (p[1]>='0' && p[1]<='9')
			&& (p[2]>='0' && p[2]<='9')
			&& (p[3]==' '))
			break;
		if (ret->len>=4 
			&& (p[0]>='0' && p[0]<='9')
			&& (p[1]>='0' && p[1]<='9')
			&& (p[2]>='0' && p[2]<='9')
			&& (p[3]=='-')) {
			multiline=1;
		}
		if (!multiline) break;
	}
	return 1;
}

int
ftp_cc_pasv(buffer *io_i, buffer *io_o, unsigned long timeout,
	stralloc *allowed_ips,stralloc *meld, unsigned int retries)
{
	stralloc x=STRALLOC_INIT;
	char *p;
	char *q;
	char *r;
	unsigned i;
	int sock;
	char ip[4];
	unsigned long p1=0,p2=0; /* keep compiler quiet */
	if (retries==0) retries=1;
	if (meld) meld->len=0;
	if (-1==ftp_cc_write_cmd_s(io_o,"PASV")) return -1;
	switch(ftp_cc_read(io_i,&x)) {
	case -1: return -1;
	case 0: return 0;
	}
	if (meld) if (-1==stralloc_copy(meld,&x)) return -1;

	if (x.len<15) return -2;
	p=x.s;
	q=p+4;
	while (*q && (*q<'0'  ||  *q>'9')) q++;
	if (!*q) {stralloc_free(&x); return -2; }
	for (i=0,r=q;*r;r++) {
		if (*r==',') {
			if (i<3) {
				*r='.'; 
				i++;
			}  else {
				unsigned int l;
				unsigned long y;
				*r='\0';
				l=scan_ulong(r+1,&y);
				if (l==0 || (i==3 && r[l+1]!=',')) 
					{stralloc_free(&x); return -2; }
				if (i++==3) p1=y;
				else p2=y;
			}
		}
	}
	/* cannot overflow the input buffer: even 3,4 is longer than 12 */
	i=str_len(q);
	if (0==ip4_scan(q,ip))
		return -2;
	q[i++]=':';
	i+=fmt_ulong(q+i,p1*256+p2);
	q[i]=0;
	for (i=0;i<allowed_ips->len;i+=4) 
		if (byte_equal(allowed_ips->s+i,4,ip))
			break;
	if (i>=allowed_ips->len)
		return -3;
	/* don't allow redirects to ports < 1024, except of 20 */
	if (p1*256+p2 <1024 && p1*256+p2 != 20)
		return -3;

	do {
	  sock=xhost_connect64(q,0,timeout,0);
	} while (-1==sock && --retries);
	stralloc_free(&x);
	return sock;
}

