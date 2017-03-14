#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "byte.h"
#include "socket.h"
#include "ip6.h"
#include "error.h"

int socket_remote6(int s,char ip[16],uint16 *port,uint32 *scope_id)
{
#ifdef HAVE_IPV6
  struct sockaddr_in6 sa;
  unsigned int sz = sizeof sa;
  if (getpeername(s,(struct sockaddr *) &sa,&sz) == -1) return -1;
  if (sa.sin6_family!=AF_INET6) { errno=error_proto; return -1; }

  byte_copy(ip,16,(char *) &sa.sin6_addr);
  uint16_unpack_big((char *) &sa.sin6_port,port);
  if (scope_id) *scope_id=sa.sin6_scope_id;
  return 0;
#else
  (void) s;
  (void) ip;
  (void) port;
  (void) scope_id;
  errno=error_afnosupport;
  return -1;
#endif
}
