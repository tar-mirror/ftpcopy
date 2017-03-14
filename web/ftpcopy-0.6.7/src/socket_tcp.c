/*
 * reimplementation of Daniel Bernstein's unix library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ndelay.h"
#include "socket.h"

int socket_tcp(void)
{
	int fd;

	fd = socket(AF_INET,SOCK_STREAM,0);
	if (fd == -1) return -1;
	if (ndelay_on (fd) == -1) {
		close (fd);
		return -1;
	}
	return fd;
}
