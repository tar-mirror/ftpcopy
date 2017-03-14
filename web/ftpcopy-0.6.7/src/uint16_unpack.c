/* Reimplementation of Daniel J. Bernsteins uint library.
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 *   Report any bugs to <uwe@ohse.de>.
 * Placed in the public domain.
 */
/* @(#) $Id: uint16_unpack.c 1.3 01/04/29 08:00:26+00:00 uwe@fjoras.ohse.de $ */
#include "uint16.h"

void
uint16_unpack (const char s[2], uint16 * u)
{
	*u = (256 * (unsigned char) s[1]) + (unsigned char) s[0];
}

void
uint16_unpack_big (const char s[2], uint16 * u)
{
	*u = (256 * (unsigned char) s[0]) + (unsigned char) s[1];
}
