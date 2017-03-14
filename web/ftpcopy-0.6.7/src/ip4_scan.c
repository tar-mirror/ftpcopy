/*
 * reimplementation of Daniel Bernstein's byte library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include "ip4.h"
#include "scan.h"

#define X(c) do { \
l=scan_ulong(s+len,&ul); if (l==0) return 0; if (ul>255) return 0; \
*(ip++)=ul; len+=l; if (c && s[len++]!=c) return 0; \
} while(0)

unsigned int
ip4_scan (const char *s, char ip[4])
{
	unsigned int l;
	unsigned int len;
	unsigned long ul;

	len = 0;
	X('.');
	X('.');
	X('.');
	X(0);
	return len;
}
