/*
 * Copyright (C) 2002 Uwe Ohse, uwe@ohse.de
 * This is free software, licensed under the terms of the GNU General 
 * Public License Version 2, of which a copy is stored at:
 *    http://www.ohse.de/uwe/licenses/GPL-2
 * Later versions may or may not apply, see 
 *    http://www.ohse.de/uwe/licenses/
 * for information after a newer version has been published.
 */
#include "stralloc.h"
#include "urlparse.h"
#include "str.h"
#include "byte.h"

#define STRDUP(x,p,l) do { if (!stralloc_copyb(x,p,l)) return -1; } while(0)
int urlparse(const char *url, stralloc *proto, stralloc *user, stralloc *pass,
	stralloc *hostport, stralloc *rest)
{
	const char *p;
	const char *q;
	/* proto://user:pass@host:port/SOME */
	p=url;
	q=url;
	if (proto) proto->len=0;
	if (user) user->len=0;
	if (pass) pass->len=0;
	if (hostport) hostport->len=0;
	if (rest) rest->len=0;
	while (*q && *q!=':') q++;
	if (!*q || q==p) return 0;
	if (proto) STRDUP(proto,p,q-p);
	q++;
	/* CISS? //<user>:<password>@<host>:<port>/<url-path> */
	if (*q!='/') { /* then it's not a common internet scheme syntax */
	  if (rest) STRDUP(rest,q,str_len(q));
	  /* now make sure that not every something:somethingelse is taken
	   * as URL. This would be annoying. */
	  if (q-p==7 && byte_equal(p,7,"mailto:")) return 1;
	  if (q-p==5 && byte_equal(p,7,"news:")) return 1;
	  return 0;
	}
	q++;
	if (*q!='/') return 0;
	q++;
	p=q;
	while (*q && *q!='@' && *q!='/') q++;
	if (*q=='@') {
		const char *r=p;
		while (r!=q && *r!=':') r++;
		if (*r==':') {
			if (user) STRDUP(user,p,r-p);
			r++;
			if (pass) STRDUP(pass,r,q-r);
		} else {
			if (user) STRDUP(user,p,q-p);
		}
		q++;
		p=q;
		while (*q && *q!='/') q++;
		if (!*q) return 0;
	}
	if (hostport) STRDUP(hostport,p,q-p);
	if (rest) STRDUP(rest,q,str_len(q));
	return 1;
}
