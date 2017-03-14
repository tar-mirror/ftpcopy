/* Reimplementation of Daniel J. Bernsteins uint library.
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 *   Report any bugs to <uwe@ohse.de>.
 * Placed in the public domain.
 */
/* @(#) $Id: uint32_pack.c 1.3 01/04/29 08:00:27+00:00 uwe@fjoras.ohse.de $ */
#include "uint32.h"

void 
uint32_pack(char t[4],uint32 u32)
{
	t[0] = u32 % 256; u32 /= 256;
	t[1] = u32 % 256; u32 /= 256;
	t[2] = u32 % 256; u32 /= 256;
	t[3] = u32;
}

void 
uint32_pack_big(char t[4],uint32 u32)
{
	t[3] = u32 % 256; u32 /= 256;
	t[2] = u32 % 256; u32 /= 256;
	t[1] = u32 % 256; u32 /= 256;
	t[0] = u32;
}
