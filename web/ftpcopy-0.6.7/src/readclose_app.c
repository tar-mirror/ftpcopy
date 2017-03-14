/*
 * reimplementation of Daniel Bernstein's unix library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include "readwrite.h"
#include "error.h"
#include "readclose.h"
#include "close.h"

int
readclose_append (int fd, stralloc * sa, unsigned int blocksize)
{
	int r;
	while (1) {
		if (!stralloc_readyplus (sa, blocksize)) {
			r=-1;
			break;
		}
		r = read (fd, sa->s + sa->len, blocksize);
		if (r == -1)
			if (errno == error_intr)
				continue;
		if (r <= 0)
			break;
		sa->len += r;
	}
	close (fd);
	return r;
}
