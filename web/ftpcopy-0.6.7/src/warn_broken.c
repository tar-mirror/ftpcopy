#include "ftpcopy.h"
#include "bailout.h"

void
warn_broken_mlsx(void)
{
  static int flag;
  if (flag++)
    return;
warning(0,"working around malformed MLSx listing. For more information",0,0,0);
warning(0,"see http://www.ohse.de/uwe/ftpcopy/faq.html#brokenmlsx.",0,0,0);
}
