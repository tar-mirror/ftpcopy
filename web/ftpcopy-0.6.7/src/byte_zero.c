/*
 * reimplementation of Daniel Bernstein's byte library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include "byte.h"

void 
byte_zero(char *s,unsigned int n)
{
	for (;;) {
		if (!n) break; 
		s[--n]=0;

		if (!n) break; 
		s[--n]=0;

		if (!n) break; 
		s[--n]=0;

		if (!n) break; 
		s[--n]=0;
	}
}
