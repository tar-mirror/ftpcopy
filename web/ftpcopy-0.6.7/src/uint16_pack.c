/* Reimplementation of Daniel J. Bernsteins uint library.
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 *   Report any bugs to <uwe@ohse.de>.
 * Placed in the public domain.
 */
/* @(#) $Id: uint16_pack.c 1.3 01/04/29 08:00:26+00:00 uwe@fjoras.ohse.de $ */
#include "uint16.h"

void
uint16_pack (char t[2], uint16 u16)
{
	t[0] = u16 % 256;
	t[1] = u16 / 256;
}

void
uint16_pack_big (char t[2], uint16 u16)
{
	t[1] = u16 % 256;
	t[0] = u16 / 256;
}
