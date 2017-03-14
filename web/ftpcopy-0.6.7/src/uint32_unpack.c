/* Reimplementation of Daniel J. Bernsteins uint library.
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 *   Report any bugs to <uwe@ohse.de>.
 * Placed in the public domain.
 */
/* @(#) $Id: uint32_unpack.c 1.4 02/02/07 11:53:30+00:00 uwe@csl42.csl-gmbh.net $ */
#include "uint32.h"

void 
uint32_unpack(const char s[4],uint32 *u)
{
	const unsigned char *t=(const unsigned char *)s;
	*u=(t[3] << 24) + (t[2] << 16) + (t[1] << 8) + t[0];
}

void 
uint32_unpack_big(const char s[4],uint32 *u)
{
	const unsigned char *t=(const unsigned char *)s;
	*u=(t[0] << 24) + (t[1] << 16) + (t[2] << 8) + t[3];
}
