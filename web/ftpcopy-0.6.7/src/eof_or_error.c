#include "bailout.h"
#include "ftpcopy.h"

void eof_or_error(int ec, int e, const char *s1,const char *s2, const char *s3)
{
  xbailout(ec,e,s1,s2,s3,e ? 0 : "unexpected end of file");
}
