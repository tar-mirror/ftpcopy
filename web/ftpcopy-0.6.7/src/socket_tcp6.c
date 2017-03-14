#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ndelay.h"
#include "socket.h"
#include "error.h"


int socket_tcp6(void)
{
#ifndef HAVE_IPV6
  errno=error_afnosupport;
  return -1;
#else
  int fd;
  fd = socket(AF_INET6,SOCK_STREAM,0);
  if (-1==fd) return -1;
  if (-1==ndelay_on(fd)) { close(fd); return -1; }
  return fd;
#endif
}

