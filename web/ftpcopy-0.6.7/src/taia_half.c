/* Reimplementation of Daniel J. Bernsteins taia library.
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 *   Report any bugs to <uwe@ohse.de>.
 * Placed in the public domain.
 */
/* @(#) $Id: taia_half.c 1.4 02/10/17 14:40:18+00:00 uwe@ranan.ohse.de $ */
#include "taia.h"

/* strange interface. i'd expected taia_half(struct taia *) */

/* XXX: breaks tai encapsulation */

#define G 1000000000UL

void
taia_half (struct taia *to, const struct taia *src)
{
	/* order of operations is important of src and to point to the same
	 * object */
	to->atto = src->atto / 2;
	if (src->nano % 2) 
		to->atto += (G/2);
	to->nano = src->nano / 2;
	if (src->sec.x % 2)
		to->nano += (G/2);
	to->sec.x = src->sec.x / 2;
}
