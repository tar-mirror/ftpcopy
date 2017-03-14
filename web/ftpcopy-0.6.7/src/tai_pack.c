/* Reimplementation of Daniel J. Bernsteins tai library.
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 *   Report any bugs to <uwe@ohse.de>.
 * Placed in the public domain.
 */
/* @(#) $Id: tai_pack.c 1.4 02/10/17 14:42:07+00:00 uwe@ranan.ohse.de $ */
#include "tai.h"
#include "uint32.h"

void
tai_pack (char *s, const struct tai *t)
{
	uint64 x;

	x = t->x;
	uint32_pack_big (s + 4, x & 0xffffffff);
	x >>= 32;
	uint32_pack_big (s, x);
}
