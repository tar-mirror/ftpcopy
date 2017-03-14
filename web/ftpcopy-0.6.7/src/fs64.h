#ifndef FS64_H
#define FS64_H

#include "uint64.h"

extern unsigned int scan_uint64(char *,uint64 *);
extern unsigned int scan_uint640(char *,uint64 *, unsigned int len);
extern unsigned int fmt_uint64(char *,uint64);

#endif
