/*
 * reimplementation of Daniel Bernstein's byte library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include "fmt.h"
#include "ip4.h"

#define X(c,d) do { \
l=fmt_ulong(s ? s+len : s,(unsigned long)(unsigned char)(c));len+=l; \
if (d) { if (s) s[len]=d; len++; } \
} while(0)

unsigned int
ip4_fmt (char *s, const char ip[4])
{
	unsigned int len=0;
	unsigned int l;
	X(ip[0],'.');
	X(ip[1],'.');
	X(ip[2],'.');
	X(ip[3],0);
	return len;
}
