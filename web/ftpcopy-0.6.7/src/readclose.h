/*
 * reimplementation of Daniel Bernstein's unix library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#ifndef READCLOSE_H
#define READCLOSE_H

#include "stralloc.h"

extern int readclose_append(int fd,stralloc *,unsigned int blocksize);
extern int readclose(int fd,stralloc *,unsigned int blocksize);

#endif
