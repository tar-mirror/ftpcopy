#ifdef DEBUG
#include <stdio.h>
#endif
#include "uo_wildmat.h"

#define MAXLEVEL 16

/* quite fast nonrecursive wildcard matching.
 * would be far more beautiful without [] and *.
 * supports:
 *  ?: match any one char
 *  *: match any number of chars, incl. 0
 *     up to 16 * per pattern are supported.
 *  [abc]: match a, b or c
 *  [a-c]: match a, b or c
 *  [-c]: match c or "-"
 *  [-]c]: match c, "-" or "]" 
 *  []c]: match c or "]" 
 *  a~b: like a*b, but definitivly stops at the next b
 */
int 
uo_wildmat (const char *pat, const char *buf, unsigned int len)
{
	unsigned int patpos[MAXLEVEL];
	unsigned int bufpos[MAXLEVEL];
	int level=0;
	char ch;
	patpos[0]=0;
	bufpos[0]=0;
#define BACKLEVEL() do { \
 if (level!=0) goto CURSE; \
 return 0; \
} while(0)
  MAIN:
#ifdef DEBUG 
printf("%d pat '%s' i %lu ,   buf '%s' i %lu, len %d\n",level,pat,patpos[level],buf,bufpos[level],len);
#endif
	for (;;) {
		ch = pat[patpos[level]++];
		if (!ch) {
			if (bufpos[level]==len)
				return 1;
			BACKLEVEL();
		}
		if (ch == '?') {
			++bufpos[level];
			continue;
		}
		if (ch == '~') { /* ~X -> skip to next X */
			ch=pat[patpos[level]];
			if (!ch)
				return 1;
			for (;;) {
				if (bufpos[level]==len)
					BACKLEVEL(); /* return 0; */
				if (buf[bufpos[level]] == ch)
					break;
				++bufpos[level];
			}
			continue;
		}
		if (ch=='*') {
			ch=pat[patpos[level]];
			if (!ch)
				return 1;
			for (;;) {
				if (bufpos[level]==len)
					BACKLEVEL(); /* return 0; */
				if (buf[bufpos[level]] == ch) {
					if (++level<MAXLEVEL) {
						patpos[level]=patpos[level-1];
						bufpos[level]=bufpos[level-1];
						goto MAIN;
					}
					CURSE: 
					level--;
					ch=pat[patpos[level]];
#ifdef DEBUG 
printf("curse\n");
printf("%d pat '%s' i %lu ,   buf '%s' i %lu, len %d\n",level,pat,patpos[level],buf,bufpos[level],len);
#endif
				}
				++bufpos[level];
			}
			continue;
		}
		if (ch=='[') {
			int got=0;
			int expect=1;
			char search=buf[bufpos[level]];
			if (pat[patpos[level]]=='^') {
				patpos[level]++;
				expect=0;
			}
			if (pat[patpos[level]]=='-') {
				if ('-'==search)
					got=1;
				patpos[level]++;
			}
			if (pat[patpos[level]]==']') {
				if (']'==search)
					got=1;
				patpos[level]++;
			}
			while (pat[patpos[level]]
				&& pat[patpos[level]]!=']') {
				if (search==pat[patpos[level]])
					got=1;
				else if (pat[patpos[level]+1]=='-'
					&& pat[patpos[level]+2]
					&& search>pat[patpos[level]] 
					&& search<=pat[patpos[level]+2])
						got=1;
				patpos[level]++;
			}
			if (pat[patpos[level]]==']')
				patpos[level]++;
			if (got!=expect)
				BACKLEVEL();
			++bufpos[level];
			continue;
		}
		if (ch == '\\')
			if (pat[patpos[level]])
				ch=pat[patpos[level]++];
		if (bufpos[level]==len)
			BACKLEVEL(); /* return 0; */
		if (buf[bufpos[level]] != ch)
			BACKLEVEL(); /* return 0; */
		++bufpos[level];
	}
}

#ifdef TEST
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int 
main(void)
{
	char buf[1024];
	int line=0;
	int ok=1;
	FILE *f;
	(void) malloc(1000); /* enforce efence linkage */
	f=fopen("uo_wildmat.in","r");
	if (!f) exit(1);
	while (fgets(buf,sizeof(buf),f)) {
		char *p,*q,*r;
		int e;
		p=strchr(buf,'\n'); if (p) *p=0;
		p=strchr(buf,' ');
		if (!p) exit(1);
		*p++=0;
		q=strchr(p,' ');
		if (!q) exit(1);
		*q++=0;
		line++;
		p=strdup(p);
		r=strdup(buf);
		e=uo_wildmat(p,r,strlen(r));
		if (e!= strtol(q,NULL,10)) {
			printf("line %d, expected %s, got %d\n"
			       "  buf=%s\n  pat=%s\n",
			       line,q,e,buf,p);
			ok=0;
		}
	}
	if (ok) printf("OK\n");
	return 0;
}
#endif
