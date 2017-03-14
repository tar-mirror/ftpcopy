#include "ftpcopy.h"
#include <sys/types.h>
#include <sys/socket.h>

void
sockrecbuf(int sock, unsigned long size)
{
  int rsize=size;
  setsockopt(sock,SOL_SOCKET,SO_RCVBUF,&rsize,sizeof(rsize));
}
