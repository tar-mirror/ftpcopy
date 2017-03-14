cat >conftest.$$.c <<EOF
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

main() {
  struct sockaddr_in6 sa;
  sa.sin6_family = AF_INET6;
  sa.sin6_scope_id=42;
}
EOF
rm -f conftest.$$.o
./auto-compile.sh -c conftest.$$.c 1>&2
x=$?
if test $x = 0 ; then
  if test -f conftest.$$.o ; then
    ok=1;
  fi
fi
if test "x$ok" = x1 ; then
  cat <<EOF
#define HAVE_IPV6 1 /* systype-info */
EOF
else
  cat <<EOF
#undef HAVE_IPV6 /* systype-info */
EOF
fi

rm conftest.$$.o
rm conftest.$$.c

