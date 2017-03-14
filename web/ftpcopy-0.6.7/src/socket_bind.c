/*
 * reimplementation of Daniel Bernstein's unix library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "byte.h"
#include "socket.h"

int socket_bind4(int fd,const char ip[4],uint16 port)
{
	struct sockaddr_in s_in;
	uint16 np;

	byte_zero((char *)&s_in,sizeof(s_in));
	s_in.sin_family = AF_INET;
	socket_htons(port,&np);
	s_in.sin_port=np;
	byte_copy((char *) &s_in.sin_addr,4,ip);

	return bind(fd,(struct sockaddr *) &s_in,sizeof(s_in));
}
