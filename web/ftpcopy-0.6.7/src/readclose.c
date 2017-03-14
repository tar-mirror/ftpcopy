/*
 * reimplementation of Daniel Bernstein's unix library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include "readclose.h"

int
readclose (int fd, stralloc * sa, unsigned int blocksize)
{
	sa->len=0;
	return readclose_append (fd, sa, blocksize);
}
