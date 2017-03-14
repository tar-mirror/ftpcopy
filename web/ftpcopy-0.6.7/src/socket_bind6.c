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
#include "error.h"

int socket_bind6(int fd,const char ip[16],uint16 port,uint32 scope_id)
{
#ifndef HAVE_IPV6
  (void) fd;
  (void) ip;
  (void) port;
  (void) scope_id;
  errno=error_afnosupport;
  return -1;
#else
  struct sockaddr_in6 si6;
  uint16 np;

  byte_zero((char *)&si6,sizeof si6);
  si6.sin6_family = AF_INET6;
  socket_htons(port,&np);
  /*  implicit: sa.sin6_flowinfo = 0; */
  byte_copy((char *) &si6.sin6_addr,16,ip);
  si6.sin6_scope_id=scope_id;
  si6.sin6_port=np;
  return bind(fd,(struct sockaddr *) &si6,sizeof si6);
#endif
}
