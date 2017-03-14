#include "socket.h"
#include "error.h"
int 
socket_udp64(void)
{
#ifdef HAVE_IPV6
  int fd;
  if (!socket_flag_noipv6) {
    fd=socket_udp6();
    if (-1!=fd) return fd;
    if (errno!=error_afnosupport)
      return -1;
  }
#endif
  if (!socket_flag_noipv4)
    return socket_udp();
  return error_afnosupport;
}
