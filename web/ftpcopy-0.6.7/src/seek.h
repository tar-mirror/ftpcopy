/*
 * reimplementation of Daniel Bernstein's unix library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#ifndef SEEK_H
#define SEEK_H

/* living without off_t can be a royal pain. -- uwe */
#include <sys/types.h>
typedef off_t seek_pos;

off_t seek_cur(int fd);
off_t seek_cur_off(int fd, off_t off);
off_t seek_set(int fd,off_t);
off_t seek_end(int fd);
off_t seek_trunc(int fd,off_t);

#define seek_begin(fd) (seek_set((fd),(off_t) 0)) 

#endif
