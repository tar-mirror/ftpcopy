#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "socket.h"

int 
socket_family(int fd)
{
  struct sockaddr_in sa4;
  int dummy;
#ifdef HAVE_IPV6
  struct sockaddr_in6 sa6;
  dummy = sizeof sa6;
  if (-1!=getsockname(fd,(struct sockaddr *) &sa6,&dummy)) {
    if (sa6.sin6_family==AF_INET6)
      return 6;
    if (sa6.sin6_family==AF_INET) /* can this happen? */
      return 4;
    return -1;
  }
#endif
  dummy = sizeof sa4;
  if (-1==getsockname(fd,(struct sockaddr *) &sa4,&dummy))
    return -1;
#ifdef AF_INET6
  if (sa4.sin_family==AF_INET6) /* however? */
    return 6;
#endif
  if (sa4.sin_family==AF_INET)
    return 4;
  return -1; /* whatever */
}
