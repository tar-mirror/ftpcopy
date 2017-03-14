#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "byte.h"
#include "socket.h"
#include "error.h"
#include "ip6.h"
#include "ip4.h"

int 
socket_connect64(int s,const char ip[16],uint16 port,uint32 scope_id)
{
#ifdef HAVE_IPV6
  if (!socket_flag_noipv6)
    return socket_connect6(s,ip,port,scope_id);
#else
  (void) scope_id;
#endif
  if (ip6_isv4mapped(ip))
    if (!socket_flag_noipv4)
      return socket_connect4(s,ip+12,port);
  if (byte_equal(ip,16,V6loopback))
    return socket_connect4(s,V4loopback,port);
  errno=error_afnosupport;
  return -1;
}
