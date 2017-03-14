/*
 * reimplementation of Daniel Bernstein's byte library.
 * placed in the public domain by Uwe Ohse, uwe@ohse.de.
 */
#include "case.h"

void
case_lowers(char *ss)
{
    unsigned char *s=ss;
	int i;
	if (!case_init_lwrdone) case_init_lwrtab();
	for (i=0;s[i];i++)
		s[i]=case_lwrtab[s[i]];
}
