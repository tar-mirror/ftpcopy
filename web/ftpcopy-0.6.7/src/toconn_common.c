/* Reimplementation of Daniel J. Bernsteins timeoutconn.
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 *   Report any bugs to <uwe@ohse.de>.
 * Placed in the public domain.
 */
/* @(#) $Id$ */
#include "error.h"
#include "iopause.h"
#include "timeoutconn.h"
#include "ndelay.h"
#include "socket.h"
#include "close.h"

int timeoutconn_finish(int fd)
{
  if (-1==ndelay_off (fd)) {
    close(fd);
    return -1;
  }
  return 0;
}

int 
timeoutconn_common(int fd, unsigned int timeout)
{
  struct taia now;
  struct taia then;
  iopause_fd iop;
  /* EWOULDBLOCK isn't needed? */
  if (errno != error_wouldblock && errno != error_inprogress)
    return -1;

  iop.fd = fd;
  iop.events = IOPAUSE_WRITE;
  taia_now (&now);
  taia_uint (&then, timeout);
  taia_add (&then, &now, &then);
  while (taia_less(&now,&then)) {
    taia_now (&now);
    iopause (&iop, 1, &then, &now);
    if (iop.revents) {
      if (!socket_connected (fd)) {
	close(fd);
	return -1;
      }
      return timeoutconn_finish(fd);
    }
  }
  close(fd); /* DJB doesn't do this. */
  errno = error_timeout;
  return -1;
}
