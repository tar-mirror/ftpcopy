#include <sys/types.h>
#include <sys/socket.h>
#include "socket.h"
#ifdef HAVE_IPV6
#include <net/if.h>
#endif
#include "socket_if.h"

uint32 socket_getifidx(const char* ifname) {
#ifdef HAVE_IPV6
  return if_nametoindex(ifname);
#else
  (void) ifname;
  return 0;
#endif
}

