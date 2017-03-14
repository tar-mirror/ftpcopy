/*
 * reimplementation of Daniel Bernstein's byte library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include "case.h"

int 
case_diffb(const char *ss,unsigned int len,const char *st)
{
	const unsigned char *s=ss;
	const unsigned char *t=st;
	unsigned char x=0;
	unsigned char y=0;
	unsigned int i;
	if (!case_init_lwrdone) case_init_lwrtab();
	for (i=0;i!=len;i++) {
		x=case_lwrtab[s[i]];
		y=case_lwrtab[t[i]];
		if (x!=y)
			break;
	}
	return ((int)(unsigned int) x) - ((int)(unsigned int) y);
}
