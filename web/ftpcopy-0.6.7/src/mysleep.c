/*
 * Copyright (C) 2002 Uwe Ohse, uwe@ohse.de
 * This is free software, licensed under the terms of the GNU General 
 * Public License Version 2, of which a copy is stored at:
 *    http://www.ohse.de/uwe/licenses/GPL-2
 * Later versions may or may not apply, see 
 *    http://www.ohse.de/uwe/licenses/
 * for information after a newer version has been published.
 */
#include "iopause.h"
#include "mysleep.h"

void
mysleep(double seconds)
{
	iopause_fd x;
	struct taia now;
	struct taia deadline;
	taia_now(&now);
	taia_uint(&deadline,seconds);
	deadline.nano=1000000000*(seconds - (int)seconds);
	deadline.atto=0;
	taia_add(&deadline,&now,&deadline);
	iopause(&x,0,&deadline,&now);
}

