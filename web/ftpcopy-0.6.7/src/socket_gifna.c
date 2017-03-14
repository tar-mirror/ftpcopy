#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include "socket_if.h"

int socket_getifname(stralloc *sa, uint32 interface) {
  char buf[IFNAMSIZ];
  char *tmp=if_indextoname(interface,buf);
  if (!tmp) return -1;
  if (!stralloc_copys(sa,buf)) return -1;
  if (!stralloc_0(sa)) return -1;
  return 0;
}
