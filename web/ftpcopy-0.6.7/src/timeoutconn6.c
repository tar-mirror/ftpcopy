/* Reimplementation of Daniel J. Bernsteins timeoutconn.
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 *   Report any bugs to <uwe@ohse.de>.
 * Placed in the public domain.
 */
/* @(#) $Id$ */
#include "error.h"
#include "timeoutconn.h"
#include "socket.h"

int timeoutconn6(int fd,char ip[16],uint16 port,unsigned int timeout,
  uint32 netif)
{
  while (1) {
    if (0==socket_connect6 (fd, ip, port,netif))
      return timeoutconn_finish(fd);
    if (errno==error_intr || errno==error_again)
      continue;
    break;
  }
  return timeoutconn_common(fd,timeout);
}

