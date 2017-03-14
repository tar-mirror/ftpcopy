/* Reimplementation of Daniel J. Bernsteins taia library.
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 *   Report any bugs to <uwe@ohse.de>.
 * Placed in the public domain.
 */
/* @(#) $Id: taia_pack.c 1.4 02/10/17 14:40:18+00:00 uwe@ranan.ohse.de $ */
#include "taia.h"
#include "uint32.h"

void
taia_pack (char *s, const struct taia *t)
{
	tai_pack (s, &t->sec);
	uint32_pack_big (s + 8, t->nano);
	uint32_pack_big (s + 12, t->atto);
}
