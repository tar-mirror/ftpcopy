/*
 * reimplementation of Daniel Bernstein's unix library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "byte.h"
#include "socket.h"

int socket_connect4(int fd,const char ip[4],uint16 port)
{
	struct sockaddr_in sa;
	uint16 np;

	byte_zero((char *)&sa,sizeof(sa));
	sa.sin_family = AF_INET;

	byte_copy((char *)&sa.sin_addr,4,ip);
	socket_htons(port,&np);
	sa.sin_port=np;

	return connect(fd,(struct sockaddr *) &sa,sizeof sa);
}
