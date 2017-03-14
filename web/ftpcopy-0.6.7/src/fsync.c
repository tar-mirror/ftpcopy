/*
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include <unistd.h>
#include "auto-have_fsync.h"
#ifndef HAVE_FSYNC
int fsync(int fd)
{
	sync();
	(void) fd;
	return 0;
}
#endif
