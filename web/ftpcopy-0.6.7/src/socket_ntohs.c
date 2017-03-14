/*
 * reimplementation of Daniel Bernstein's unix library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include <stddef.h>
#include "socket.h"
void 
socket_ntohs (uint16 nport, uint16 *hport)
{
	unsigned char *p=(char *)&nport;
	*hport=p[0]*256 + p[1];
}

