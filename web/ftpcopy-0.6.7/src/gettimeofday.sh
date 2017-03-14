#! /bin/sh
#
# try to find gettimeofday
#
FILE=conftest.$$
set -e

cat >$FILE.c <<EOF
int main() {
	return gettimeofday();
}
EOF
./auto-compile.sh -c $FILE.c  2>/dev/null >/dev/null # die if failure
for i in "" -lsocket ; do
  if ./auto-link.sh $FILE $FILE.o $i 2>/dev/null >/dev/null ; then
    if test "x$i" = x ; then 
      echo
      echo "GETTIMEOFDAY: STDLIB /* systype-info */"
    else
      echo "$i"
      x=`echo "$i" | tr '-A-Z.' '_a-z_'`
      echo "GETTIMEOFDAY: $x /* systype-info */"
    fi
    rm -f $FILE.c $FILE.o $FILE
    exit 0;
  fi
done
rm -f $FILE.c $FILE.o $FILE
