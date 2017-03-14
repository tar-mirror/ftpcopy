/*
 * reimplementation of Daniel Bernstein's unix library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include <sys/types.h>
#include <fcntl.h>
#include "open.h"

int open_append_mode(const char *fname,int mode)
{ return open(fname,O_WRONLY | O_APPEND | O_CREAT | O_NDELAY,mode); }
int open_append(const char *fname)
{ return open(fname,O_WRONLY | O_APPEND | O_CREAT | O_NDELAY,0600); }
int open_append_blocking(const char *fname,int mode)
{ return open(fname,O_WRONLY | O_APPEND | O_CREAT,mode); }

