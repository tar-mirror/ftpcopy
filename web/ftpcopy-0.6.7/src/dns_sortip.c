/*
 * Daniel Bernstein's dns library.
 * Taken from djbdns-1.05.
 *
 * The djbdns library is now in the public domain, according to
 * <20020704164247.30990.qmail@cr.yp.to> from 2002-07-04 on bugtraq.
 */
#include "byte.h"
#include "dns.h"

/* XXX: sort servers by configurable notion of closeness? */
/* XXX: pay attention to competence of each server? */

void dns_sortip(char *s,unsigned int n)
{
  unsigned int i;
  char tmp[4];

  n >>= 2;
  while (n > 1) {
    i = dns_random(n);
    --n;
    byte_copy(tmp,4,s + (i << 2));
    byte_copy(s + (i << 2),4,s + (n << 2));
    byte_copy(s + (n << 2),4,tmp);
  }
}
