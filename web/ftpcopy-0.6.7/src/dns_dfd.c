/*
 * Daniel Bernstein's dns library.
 * Taken from djbdns-1.05.
 *
 * The djbdns library is now in the public domain, according to
 * <20020704164247.30990.qmail@cr.yp.to> from 2002-07-04 on bugtraq.
 */
#include "error.h"
#include "alloc.h"
#include "byte.h"
#include "dns.h"

int dns_domain_fromdot(char **out,const char *buf,unsigned int n)
{
  char label[63];
  unsigned int labellen = 0; /* <= sizeof label */
  char name[255];
  unsigned int namelen = 0; /* <= sizeof name */
  char ch;
  char *x;

  errno = error_proto;

  for (;;) {
    if (!n) break;
    ch = *buf++; --n;
    if (ch == '.') {
      if (labellen) {
	if (namelen + labellen + 1 > sizeof name) return 0;
	name[namelen++] = labellen;
	byte_copy(name + namelen,labellen,label);
	namelen += labellen;
	labellen = 0;
      }
      continue;
    }
    if (ch == '\\') {
      if (!n) break;
      ch = *buf++; --n;
      if ((ch >= '0') && (ch <= '7')) {
	ch -= '0';
	if (n && (*buf >= '0') && (*buf <= '7')) {
	  ch <<= 3;
	  ch += *buf - '0';
	  ++buf; --n;
	  if (n && (*buf >= '0') && (*buf <= '7')) {
	    ch <<= 3;
	    ch += *buf - '0';
	    ++buf; --n;
	  }
	}
      }
    }
    if (labellen >= sizeof label) return 0;
    label[labellen++] = ch;
  }

  if (labellen) {
    if (namelen + labellen + 1 > sizeof name) return 0;
    name[namelen++] = labellen;
    byte_copy(name + namelen,labellen,label);
    namelen += labellen;
    labellen = 0;
  }

  if (namelen + 1 > sizeof name) return 0;
  name[namelen++] = 0;

  x = alloc(namelen);
  if (!x) return 0;
  byte_copy(x,namelen,name);

  if (*out) alloc_free(*out);
  *out = x;
  return 1;
}
