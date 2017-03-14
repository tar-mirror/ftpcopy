/* Reimplementation of Daniel J. Bernsteins timeoutconn.
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 *   Report any bugs to <uwe@ohse.de>.
 * Placed in the public domain.
 */
/* @(#) $Id: timeoutconn.h 1.4 02/10/17 12:19:45+00:00 uwe@ranan.ohse.de $ */
#ifndef TIMEOUTCONN_H
#define TIMEOUTCONN_H
#include "uint16.h"
#include "uint32.h"

extern int timeoutconn6(int fd, char *ip4, uint16 port, 
	unsigned int timeout, uint32 netif);
extern int timeoutconn64(int fd, char *ip4, uint16 port, 
	unsigned int timeout, uint32 netif);
extern int timeoutconn(int fd, char *ip4, uint16 port, 
	unsigned int timeout);
int timeoutconn_finish(int fd);
int timeoutconn_common(int fd, unsigned int timeout);


#endif
