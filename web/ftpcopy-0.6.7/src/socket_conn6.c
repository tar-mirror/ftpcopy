#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "byte.h"
#include "socket.h"
#include "error.h"

int 
socket_connect6(int s,const char ip[16],uint16 port,uint32 scope_id)
{
#ifndef HAVE_IPV6
  (void) s;
  (void) ip;
  (void) port;
  (void) scope_id;
  errno=error_afnosupport;
  return -1;
#else
  struct sockaddr_in6 sa;
  
  byte_zero((char *)&sa,sizeof sa);
  sa.sin6_family = AF_INET6;
  uint16_pack_big((char *) &sa.sin6_port,port);
  sa.sin6_scope_id = scope_id;
  byte_copy((char *) &sa.sin6_addr,16,ip);

  return connect(s,(struct sockaddr *) &sa,sizeof sa);
#endif

}
