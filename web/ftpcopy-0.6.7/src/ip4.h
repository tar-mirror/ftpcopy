/*
 * reimplementation of Daniel Bernstein's byte library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#ifndef IP4_H
#define IP4_H

extern unsigned int ip4_scan(const char *,char *);
#define IP4_FMT 20
extern unsigned int ip4_fmt(char *,const char *);

extern const unsigned char V4loopback[4];

#endif
