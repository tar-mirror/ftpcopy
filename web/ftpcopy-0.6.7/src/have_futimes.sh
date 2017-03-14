#! /bin/sh
#
set -e

FILE=conftest$$
DEFINE=undef

#
cat >$FILE.c <<EOF
#include <sys/types.h>
#include <errno.h>
static char dummy[128];
int main(int argc,char **argv)
{
  if (!futimes(argv[1],dummy)) return 0;
  if (errno==ENOSYS) return 27;
  return 0;
}
EOF
if ./auto-compile.sh -c $FILE.c >&2 ; then
  for i in "" $libs ; do
    if test "x$i" = x ; then
      l=""
    else
      l="-l$i"
    fi
    # >&2 because we use the stdout of this script, and the MAC OS X linker
    # thinks the error messages belong on stdout.
    if ./auto-link.sh $FILE $FILE.o $l >&2 ; then
      if ./$FILE; then                                                         
        DEFINE=define                                                          
      elif [ "$?" = 27 ]; then                                                 
        STUB="stub function"                                                   
      fi
    fi
  done
fi

cat <<EOF
#ifndef auto_have_futimes_h
#define auto_have_futimes_h
#$DEFINE HAVE_FUTIMES /* systype-info: $STUB */
#endif
EOF
rm -f $FILE $FILE.c $FILE.o
