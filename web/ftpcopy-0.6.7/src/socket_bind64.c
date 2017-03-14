#include "socket.h"
#include "error.h"
int 
socket_bind64(int sock,const char *ip,uint16 port,uint32 scope_id)
{
#ifdef HAVE_IPV6
  if (!socket_flag_noipv6) {
    if (!socket_bind6(sock,ip,port,scope_id))
      return 0;
  }
#else
  (void) scope_id;
#endif
  if (!socket_flag_noipv4)
    return socket_bind4(sock,ip,port);
  return error_afnosupport;
}

