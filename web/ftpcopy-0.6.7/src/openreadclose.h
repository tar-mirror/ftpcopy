/*
 * reimplementation of Daniel Bernstein's unix library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#ifndef OPENREADCLOSE_H
#define OPENREADCLOSE_H

#include "stralloc.h"

extern int openreadclose(const char *fname,stralloc *,unsigned int blocksize);

#endif
