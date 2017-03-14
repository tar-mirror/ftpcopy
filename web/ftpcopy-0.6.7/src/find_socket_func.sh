#! /bin/sh
#
# try to find socket
#
FILE=conftest.$$
cat >$FILE.c <<EOF
int main() {
	if (socket()) return gethostbyname();
	else return 0;
}
EOF

./auto-compile.sh -c $FILE.c  2>/dev/null >/dev/null
for i in "" -lsocket "-lsocket -lnsl" ; do
  if ./auto-link.sh $FILE $FILE.o $i 2>/dev/null >/dev/null ; then
    if test "x$i" = x ; then 
      echo
      echo "SOCKET: STDLIB /* systype-info */"
    else
      echo "$i"
      x=`echo "$i" | tr 'ABCDEFGHIJKLMNOPQRSTUVWXYZ.-' \
                        'abcdefghijklmnopqrstuvwxyz__' `
      echo "SOCKET: $x /* systype-info */"
    fi
    rm -f $FILE.c $FILE.o $FILE
    exit 0;
  fi
done
rm -f $FILE.c $FILE.o $FILE
