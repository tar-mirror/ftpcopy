#include "stralloc.h"
#include "ftpcopy.h"
#include "bailout.h"

stralloc *
canon(stralloc *l_dir) /* feed me with 0 terminated strings only */
{
  static stralloc c=STRALLOC_INIT;
  char *p,*w;
  if (!stralloc_ready(&c,l_dir->len+1)) oom();

  p=l_dir->s;
  w=c.s;
  while (*p) {	
    /* ^../any ->  ^any */
    if (p==l_dir->s && p[0]=='.' && p[1]=='.' &&  (p[2]=='/' || p[2]==0)) {	
      p+=3;
    } else if (p[0]=='/' || p==l_dir->s) {
      if (p[0]=='/') p++;
      if (p[0]=='/') continue;
      if (*p=='.' && p[1]=='.' && (p[2]=='/' || p[2]==0)) {	
	while (w!=c.s &&w[-1]!='/') 
	  w--;
	if (w!=c.s) w--;
	p+=2;
	continue;
      } else if ((l_dir->s[0]=='/'||w!=c.s) && (w==c.s || w[-1]!='/'))
	*w++='/';
    }
    *w++=*p++;
  }
  c.len=w-c.s;
  if (!stralloc_0(&c)) oom();
  return &c;
}

#ifdef TEST
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef LONGTEST
static stralloc *
old_canon(stralloc *l_dir) /* feed me with 0 terminated strings only */
{
static stralloc c=STRALLOC_INIT;
char *p,*end,*w;
if (!stralloc_copy(&c,l_dir)) oom();
if (!stralloc_readyplus(&c,l_dir->len+1)) oom();
p=l_dir->s;
end=l_dir->s+l_dir->len;
w=c.s;

while (*p) {  
if (p[0]=='/' && p[1]=='.' && p[2]=='.' && (!p[3] || p[3]=='/')) {
while (w!=c.s && w[-1]!='/') w--;
*w='/';
p+=4;
} else if (p[0]=='/' && p[1]=='/')
p++;
else
*w++=*p++;
}
c.len=w-c.s;
if (!stralloc_0(&c)) oom();
return &c;
}

static stralloc *
gra_canon(stralloc *l_dir) /* feed me with 0 terminated strings only */
{
  static stralloc c=STRALLOC_INIT;
  char *p,*end,*w,*v;
  if (!stralloc_copy(&c,l_dir)) oom();
  if (!stralloc_readyplus(&c,l_dir->len+1)) oom();
  p=l_dir->s;
  end=l_dir->s+l_dir->len;
  w=c.s;

  while (*p) {  
    if (p[0]=='/' && p[1]=='.' && p[2]=='.' && (!p[3] || p[3]=='/')) {
      v=w;                                                                     
      while (v!=c.s && v[-1]!='/') v--;                                        
      if (v+2==w && v[0]=='.' && v[1]=='.') {                                  
        *w++=*p++;                                                             
      } else {                                                                 
        w=v;                                                                   
        p+=3;                                                                  
       if (*p) p++;                                                            
      }                                                                        
    }                                                                          
    else if ((p==l_dir->s || p[-1]=='/') && p[0]=='.' && p[1]=='/')            
      p+=2;                                                                    
    else if (p[0]=='/' && p[1]=='/')        
      p++;
    else
    *w++=*p++;
  }
  c.len=w-c.s;
  if (!stralloc_0(&c)) oom();
  return &c;
}
#endif


int main(int argc, char **argv)
{
  char buf[1024];
  static stralloc sa;
  stralloc *sa2;
  while (fgets(buf,sizeof(buf),stdin)) {
    char *p;
    char *c=strchr(buf,'\n');
    int x;
    if (c) *c=0;
    if (!stralloc_copys(&sa,buf)) _exit(1);
    if (!stralloc_0(&sa)) _exit(1);
    printf("in : %s:\n",buf);
    sa2=canon(&sa);
    printf("out: %s:\n",sa2->s);
#ifdef LONGTEST
    sa2=old_canon(&sa);
    printf("old: %s:\n",sa2->s);
    sa2=gra_canon(&sa);
    printf("gra: %s:\n",sa2->s);
#endif
  }
}
#endif
