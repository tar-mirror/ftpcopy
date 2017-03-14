/*
 * reimplementation of Daniel Bernstein's unix library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include <stddef.h>
#include "socket.h"
void 
socket_htons (uint16 hport, uint16 *nport)
{
	unsigned char *p=(char *)nport;
	p[0]=hport / 256;
	p[1]=hport % 256;
	return;
}

