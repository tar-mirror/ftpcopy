#! /bin/sh
# try to find fsync
#
set -e
FILE=conftest$$
cat >$FILE.c <<EOF
#include <unistd.h>
int main() {
	return fsync(1);
}
EOF
if ./auto-compile.sh -c $FILE.c  2>/dev/null >/dev/null ; then
  if ./auto-link.sh $FILE $FILE.o $i 2>/dev/null >/dev/null ; then
    if test $? -eq 0 ; then
      rm -f $FILE.c $FILE.o $FILE
      exit 0;
    fi
  fi
fi
rm -f $FILE.c $FILE.o $FILE
echo "warning: fsync not found, using sync as replacement" >&2
./auto-compile.sh -c fsync.c && echo "fsync.o"
