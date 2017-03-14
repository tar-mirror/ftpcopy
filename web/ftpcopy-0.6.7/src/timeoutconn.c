/* Reimplementation of Daniel J. Bernsteins timeoutconn.
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 *   Report any bugs to <uwe@ohse.de>.
 * Placed in the public domain.
 */
/* @(#) $Id: timeoutconn.c 1.6 02/10/17 14:33:38+00:00 uwe@ranan.ohse.de $ */
#include "error.h"
#include "timeoutconn.h"
#include "socket.h"

int
timeoutconn (int fd, char ip[4], uint16 port, unsigned int timeout)
{
  while (1) {
    if (0==socket_connect4 (fd, ip, port))
      return timeoutconn_finish(fd);
    if (errno==error_intr || errno==error_again)
      continue;
    break;
  }
  return timeoutconn_common(fd,timeout);
}
