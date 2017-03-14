#ifndef SOCKET_IF_H
#define SOCKET_IF_H
#include "stralloc.h"
#include "uint32.h"
int socket_getifname(stralloc *sa, uint32 idx);
uint32 socket_getifidx(const char *ifname);
#endif
