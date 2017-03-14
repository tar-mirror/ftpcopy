#! /bin/sh
#usage: gettype TYPE ERSATZ headers
type="$1"
ersatz="$2"
FILE=conftest$$
shift
shift
set -e

for i in "" "$@" ; do
  if test "x$i" = x ; then
    headers="";
  else
    headers="";
    for j in $i ; do
      headers="$headers
#include <$j> /* systype-info for $type */"
    done
  fi
cat >$FILE.c <<EOF
$headers
int main()
{
	$type t; 
	return sizeof(t);
}
EOF
  rm -f $FILE.o
  if ./auto-compile.sh -c $FILE.c >/dev/null 2>/dev/null ; then
    echo "$headers"
    rm -f $FILE.c $FILE.o $FILE
    exit 0
  fi

done
echo "#define $type $ersatz /* systype-info */"
echo "warning: $type not found, using $ersatz" >&2
rm -f $FILE.c $FILE.o $FILE
exit 0
