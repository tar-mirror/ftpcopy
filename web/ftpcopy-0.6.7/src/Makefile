VERSION=0.6.7
PACKAGE=ftpcopy
CLASS=web


INCLUDES=-I.

CC=gcc
L=./auto-link.sh
C=./auto-compile.sh
W=./auto-compilew.sh
MYMAKE=make
PACKAGE_VERSION=$(PACKAGE)-$(VERSION)
PREMAKE_DEFS=-DPACKAGE_VERSION=\"$(PACKAGE)-$(VERSION)\" \
 -DPACKAGE=\"$(PACKAGE)\" -DVERSION=\"$(VERSION)\" -DPACKAGE_CLASS=\"$(CLASS)\"

TARGETS=$(EXTRA_TARGETS) $(PREMAKE_TARGETS)
CLEANFILES=$(EXTRA_CLEANFILES) $(PREMAKE_CLEANFILES)
MAINTAINER_CLEANFILES=$(EXTRA_MAINTAINER_CLEANFILES) $(PREMAKE_MAINTAINER_CLEANFILES)
PREMAKE_DIST=$(PACKAGE_VERSION).tar.gz
#
#
# the dependency of socket_ux on ipv6 is here because premake2 can't 
# handle it otherwise.


#!T:testsort:testsort.c ssort.c:libunix.a libbyte.a


PREMAKE_TARGETS = ftpcopy ftpls ftpcp.1 ftpcopy.1 ftpls.1 ftpcopy.html \
ftpls.html
 
PREMAKE_CLEANFILES = *.da *.bb *.bbg check.out conftest.c conftest \
conftest.o auto-socket.lib fsync.o auto-fsync.lib utimes.o \
auto-utimes.lib auto-gettimeofday.lib auto-version.tmac ftpcp.html.t \
install.html.t INSTALL.t ftpcp.1 ftpcp.1.t ftpcopy.1 ftpcopy.1.t \
ftpls.1 ftpls.1.t ftpcopy.html ftpcopy.html.t ftpls.html ftpls.html.t \
auto-typesize.h auto-typesize.stamp auto-socklen_t.h \
auto-socklen_t.stamp auto-socklen_t.h.t auto-have_futimes.h *.stamp
 
PREMAKE_MAINTAINER_CLEANFILES = ftpcp.html install.html INSTALL
 

libbyte_a_OBJECTS=byte_chr.o byte_copy.o byte_cr.o byte_diff.o \
byte_zero.o case_diffb.o case_lowerb.o case_lowers.o case_lwrtab.o \
case_startb.o case_starts.o fmt_uint0.o fmt_uint64.o fmt_ulong.o \
fmt_xlong.o ip4_constants.o ip4_fmt.o ip4_scan.o ip6_constants.o \
ip6_fmt.o ip6_scan.o scan_long.o scan_sign.o scan_ulong.o scan_xlong.o \
str_chr.o str_diff.o str_len.o str_rchr.o str_start.o uint16_pack.o \
uint16_unpack.o uint32_pack.o uint32_unpack.o
 
libdns_a_OBJECTS=dns_dfd.o dns_domain.o dns_ip.o dns_ip6.o dns_ip64.o \
dns_ipq.o dns_ipq6.o dns_ipq64.o dns_packet.o dns_random.o dns_rcip.o \
dns_rcrw.o dns_resolve.o dns_sortip.o dns_sortip6.o dns_transmit.o
 
libstrhash_a_OBJECTS=strhash_crea.o strhash_dest.o strhash_ente.o \
strhash_get.o strhash_hash.o strhash_look.o
 
libtai_a_OBJECTS=tai_add.o tai_now.o tai_pack.o tai_sub.o tai_uint.o \
taia_add.o taia_approx.o taia_frac.o taia_half.o taia_less.o \
taia_now.o taia_pack.o taia_sub.o taia_uint.o
 
libunix_a_OBJECTS=alloc.o alloc_re.o api_futimes.o api_utimes.o \
buffer.o buffer_0.o buffer_1.o buffer_2.o buffer_get.o buffer_put.o \
env_get.o error.o error_str.o gen_alloc_ady.o gen_alloc_end.o \
gen_alloc_lus.o get_cwd.o getln.o iopause.o ndelay_off.o ndelay_on.o \
open_append.o open_excl.o open_read.o openreadclose.o readclose.o \
readclose_app.o sig.o sig_catch.o socket_bind.o socket_bind6.o \
socket_bind64.o socket_conn.o socket_conn6.o socket_conn64.o \
socket_connt.o socket_family.o socket_flag.o socket_gifid.o \
socket_gifna.o socket_htons.o socket_ntohs.o socket_remote6.o \
socket_tcp.o socket_tcp6.o socket_tcp64.o socket_udp.o socket_udp6.o \
socket_udp64.o stralloc_cat.o stralloc_catb.o stralloc_cats.o \
stralloc_copy.o stralloc_eady.o stralloc_free.o stralloc_opyb.o \
stralloc_opys.o stralloc_pend.o stralloc_plus.o
 
libuomisc_a_OBJECTS=api_dir.o bailout.o bailout_name.o host_connect4.o \
host_connect64.o timeoutconn.o timeoutconn6.o toconn_common.o \
uo_wildmat.o uogetopt.o
 
libuotime_a_OBJECTS=uo_now.o uo_sec702dt.o yyyy_mm_dd.o
 
PREMAKE_EXTRA_SYSTYPE =  auto-socket.lib auto-have_fsync.h \
auto-have_utimes.h auto-gettimeofday.lib auto-typesize.h \
auto-have_ipv6.h auto-socklen_t.h auto-iopause.h auto-have_futimes.h
 
all:  auto-systype $(TARGETS) $(EXTRA_TARGETS)
 
auto-socket.lib: find_socket_func.sh auto-compile.sh auto-link.sh
	sh find_socket_func.sh >auto-socket.t && mv auto-socket.t $@
auto-have_fsync.h: have_func.sh
	sh have_func.sh fsync "#include <unistd.h>" "fsync(0)" "" "" >$@.t && mv $@.t $@
auto-fsync.lib: fsync.sh auto-compile.sh auto-link.sh auto-have_fsync.h
	sh fsync.sh >fsync.t && mv fsync.t $@
auto-have_utimes.h: have_func.sh auto-compile.sh auto-link.sh
	sh have_func.sh utimes "#include <sys/time.h>" "utimes(0,0)" "" "" >$@.t && mv $@.t $@
auto-utimes.lib: replace.sh auto-compile.sh auto-link.sh auto-have_utimes.h
	sh replace.sh utimes utimes "" -lsocket >$@.t && mv $@.t $@
auto-gettimeofday.lib: gettimeofday.sh auto-compile.sh auto-link.sh
	sh gettimeofday.sh >gettimeofday.t && mv gettimeofday.t $@
ftpcopy:  ftpcopy.o ftpparse.o ftplib.o ftp_read_lis.o urlparse.o canon.o common.o mdtm.o mysleep.o warn_broken.o eof_or_error.o utcdate2tai.o sockrecbuf.o ssort.o inq_winsize.o libuotime.a libuomisc.a libdns.a libstrhash.a libunix.a libtai.a libbyte.a auto-socket.lib auto-fsync.lib auto-utimes.lib auto-gettimeofday.lib auto-link.sh
	$L ftpcopy  ftpcopy.o ftpparse.o ftplib.o ftp_read_lis.o urlparse.o canon.o common.o mdtm.o mysleep.o warn_broken.o eof_or_error.o utcdate2tai.o sockrecbuf.o ssort.o inq_winsize.o libuotime.a libuomisc.a libdns.a libstrhash.a libunix.a libtai.a libbyte.a `head -n 1 auto-socket.lib` `head -n 1 auto-fsync.lib` `head -n 1 auto-utimes.lib` `head -n 1 auto-gettimeofday.lib` 
ftpls:  ftpls.o ftpparse.o ftplib.o ftp_read_lis.o urlparse.o sort_it.o common.o mysleep.o warn_broken.o eof_or_error.o utcdate2tai.o ssort.o libuotime.a libdns.a libuomisc.a libstrhash.a libdns.a libunix.a libtai.a libbyte.a auto-socket.lib auto-gettimeofday.lib auto-link.sh
	$L ftpls  ftpls.o ftpparse.o ftplib.o ftp_read_lis.o urlparse.o sort_it.o common.o mysleep.o warn_broken.o eof_or_error.o utcdate2tai.o ssort.o libuotime.a libdns.a libuomisc.a libstrhash.a libdns.a libunix.a libtai.a libbyte.a `head -n 1 auto-socket.lib` `head -n 1 auto-gettimeofday.lib` 
auto-typesize.h: auto-typesize.stamp
auto-typesize.stamp: typesize.sh auto-compile.sh auto-link.sh
	sh typesize.sh >typesize.t
	@if cmp typesize.t auto-typesize.h 2>/dev/null >/dev/null ; then : ; else mv typesize.t auto-typesize.h ; fi
	rm -f typesize.t
	touch $@
auto-socklen_t.h: auto-socklen_t.stamp
auto-socklen_t.stamp: checktype.sh auto-compile.sh auto-link.sh
	sh checktype.sh socklen_t int sys/types.h "sys/types.h sys/socket.h" >auto-socklen_t.h.t
	@if cmp auto-socklen_t.h.t auto-socklen_t.h 2>/dev/null >/dev/null ; then : ; else mv auto-socklen_t.h.t auto-socklen_t.h ; fi
	@rm -f auto-socklen_t.h.t
	@touch $@
auto-have_ipv6.h:auto-compile.sh have_ipv6.sh
	sh have_ipv6.sh >$@.tmp
	mv $@.tmp $@ 
auto-iopause.h: iopause.sh auto-compile.sh auto-link.sh
	sh iopause.sh >iopause.t && mv iopause.t $@
auto-have_futimes.h: have_futimes.sh auto-compile.sh auto-link.sh have_func.sh
	sh have_futimes.sh >$@.t && mv $@.t $@
libbyte.a: $(libbyte_a_OBJECTS) auto-makelib.sh
	./auto-makelib.sh $@ $(libbyte_a_OBJECTS)
libdns.a: $(libdns_a_OBJECTS) auto-makelib.sh
	./auto-makelib.sh $@ $(libdns_a_OBJECTS)
libstrhash.a: $(libstrhash_a_OBJECTS) \
auto-makelib.sh
	./auto-makelib.sh $@ $(libstrhash_a_OBJECTS)
libtai.a: $(libtai_a_OBJECTS) auto-makelib.sh
	./auto-makelib.sh $@ $(libtai_a_OBJECTS)
libunix.a: $(libunix_a_OBJECTS) auto-makelib.sh
	./auto-makelib.sh $@ $(libunix_a_OBJECTS)
libuomisc.a: $(libuomisc_a_OBJECTS) auto-makelib.sh
	./auto-makelib.sh $@ $(libuomisc_a_OBJECTS)
libuotime.a: $(libuotime_a_OBJECTS) auto-makelib.sh
	./auto-makelib.sh $@ $(libuotime_a_OBJECTS)
ftpcp.html: ftpcp.1.in groff.tmac auto-version.tmac
	groff -mwww -Thtml -P-l groff.tmac auto-version.tmac ftpcp.1.in\
	| sed -e 's%</head>%<link rel="SHORTCUT ICON" \
href="http://www.ohse.de/uwe/ftpcopy/ftpcopy.ico"></head>%' \
>ftpcp.html.t && mv ftpcp.html.t ftpcp.html
install.html: install.0.in groff.tmac auto-version.tmac
	groff -mwww -Thtml -P-l groff.tmac auto-version.tmac install.0.in\
	| sed -e 's%</head>%<link rel="SHORTCUT ICON" \
href="http://www.ohse.de/uwe/ftpcopy/ftpcopy.ico"></head>%' \
>install.html.t && mv install.html.t install.html
INSTALL: install.0.in groff.tmac auto-version.tmac
	groff -man -Tascii groff.tmac auto-version.tmac install.0.in |sed \
's/\o33\[[0-9]*m//g ' |col -b >INSTALL.t && mv INSTALL.t \
INSTALL
ftpcp.1: ftpcp.1.in groff.tmac auto-version.tmac
	cat groff.tmac auto-version.tmac ftpcp.1.in \
 | sed 's/^.section/.SH/' >ftpcp.1.t \
 && mv ftpcp.1.t ftpcp.1
ftpcopy.1: ftpcopy uogo2man
	perl uogo2man ftpcopy ./ftpcopy 1 man "--include-exclude-help" \
"IN/EXCLUDE" >$@.t &&mv $@.t $@
ftpls.1: ftpls uogo2man
	perl uogo2man ftpcopy ./ftpls 1 man  >$@.t &&mv $@.t $@
ftpcopy.html: ftpcopy uogo2man doc-header.html
	perl uogo2man ftpcopy ./ftpcopy - html "--include-exclude-help" \
"IN/EXCLUDE" >$@.t &&mv $@.t $@
ftpls.html: ftpls uogo2man doc-header.html
	perl uogo2man ftpcopy ./ftpls - html  >$@.t &&mv $@.t \
$@
auto-version.tmac: version.tmac.stamp
version.tmac.stamp: Makefile
	(echo .ds PA $(PACKAGE) ;\
	 echo .ds VE $(VERSION) ;\
	 echo .ds CL $(CLASS) ;\
	) >auto-version.tmac.t
	cmp auto-version.tmac auto-version.tmac.t \
	 || cp auto-version.tmac.t auto-version.tmac
	touch $@ && rm auto-version.tmac.t
html: ftpcp.html install.html INSTALL ftpcopy.html ftpls.html

 
alloc.o: alloc.c alloc.h error.h auto-compilew.sh
	$W  -c alloc.c
alloc_re.o: alloc_re.c alloc.h byte.h auto-compilew.sh
	$W  -c alloc_re.c
api_dir.o: api_dir.c stralloc.h gen_alloc.h str.h api_dir.h auto-compilew.sh
	$W  -c api_dir.c
api_futimes.o: api_futimes.c auto-have_futimes.h api_futimes.h \
 api_utimes.h auto-compilew.sh
	$W  -c api_futimes.c
api_utimes.o: api_utimes.c api_utimes.h auto-compilew.sh
	$W  -c api_utimes.c
bailout.o: bailout.c error.h buffer.h bailout.h fmt.h auto-compilew.sh
	$W  -c bailout.c
bailout_name.o: bailout_name.c bailout.h buffer.h auto-compilew.sh
	$W  -c bailout_name.c
buffer.o: buffer.c buffer.h auto-compile.sh
	$C  -c buffer.c
buffer_0.o: buffer_0.c readwrite.h buffer.h auto-compile.sh
	$C  -c buffer_0.c
buffer_1.o: buffer_1.c readwrite.h buffer.h auto-compile.sh
	$C  -c buffer_1.c
buffer_2.o: buffer_2.c readwrite.h buffer.h auto-compile.sh
	$C  -c buffer_2.c
buffer_get.o: buffer_get.c buffer.h byte.h error.h auto-compile.sh
	$C  -c buffer_get.c
buffer_put.o: buffer_put.c buffer.h str.h byte.h error.h auto-compile.sh
	$C  -c buffer_put.c
byte_chr.o: byte_chr.c byte.h auto-compilew.sh
	$W  -c byte_chr.c
byte_copy.o: byte_copy.c byte.h auto-compilew.sh
	$W  -c byte_copy.c
byte_cr.o: byte_cr.c byte.h auto-compilew.sh
	$W  -c byte_cr.c
byte_diff.o: byte_diff.c byte.h auto-compilew.sh
	$W  -c byte_diff.c
byte_zero.o: byte_zero.c byte.h auto-compilew.sh
	$W  -c byte_zero.c
canon.o: canon.c stralloc.h gen_alloc.h ftpcopy.h buffer.h \
 attributes.h bailout.h auto-compilew.sh
	$W  -c canon.c
case_diffb.o: case_diffb.c case.h auto-compilew.sh
	$W  -c case_diffb.c
case_lowerb.o: case_lowerb.c case.h auto-compilew.sh
	$W  -c case_lowerb.c
case_lowers.o: case_lowers.c case.h auto-compilew.sh
	$W  -c case_lowers.c
case_lwrtab.o: case_lwrtab.c case.h auto-compilew.sh
	$W  -c case_lwrtab.c
case_startb.o: case_startb.c case.h auto-compilew.sh
	$W  -c case_startb.c
case_starts.o: case_starts.c case.h auto-compilew.sh
	$W  -c case_starts.c
common.o: common.c buffer.h attributes.h stralloc.h gen_alloc.h str.h \
 ftplib.h bailout.h byte.h ftpcopy.h error.h timeoutio.h taia.h tai.h \
 uint64.h typesize.h auto-typesize.h iopause.h auto-iopause.h \
 host_connect.h readwrite.h close.h mysleep.h ip6.h socket.h uint16.h \
 uint32.h auto-have_ipv6.h socket_if.h scan.h auto-compilew.sh
	$W  -c common.c
dns_dfd.o: dns_dfd.c error.h alloc.h byte.h dns.h stralloc.h \
 gen_alloc.h iopause.h auto-iopause.h taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compile.sh
	$C  -c dns_dfd.c
dns_domain.o: dns_domain.c error.h alloc.h case.h byte.h dns.h \
 stralloc.h gen_alloc.h iopause.h auto-iopause.h taia.h tai.h uint64.h \
 typesize.h auto-typesize.h auto-compile.sh
	$C  -c dns_domain.c
dns_ip.o: dns_ip.c stralloc.h gen_alloc.h uint16.h typesize.h \
 auto-typesize.h byte.h dns.h iopause.h auto-iopause.h taia.h tai.h \
 uint64.h auto-compile.sh
	$C  -c dns_ip.c
dns_ip6.o: dns_ip6.c stralloc.h gen_alloc.h uint16.h typesize.h \
 auto-typesize.h byte.h dns.h iopause.h auto-iopause.h taia.h tai.h \
 uint64.h ip4.h ip6.h auto-compile.sh
	$C  -c dns_ip6.c
dns_ip64.o: dns_ip64.c stralloc.h gen_alloc.h uint16.h typesize.h \
 auto-typesize.h byte.h dns.h iopause.h auto-iopause.h taia.h tai.h \
 uint64.h ip4.h ip6.h auto-compile.sh
	$C  -c dns_ip64.c
dns_ipq.o: dns_ipq.c stralloc.h gen_alloc.h case.h byte.h str.h dns.h \
 iopause.h auto-iopause.h taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compile.sh
	$C  -c dns_ipq.c
dns_ipq6.o: dns_ipq6.c stralloc.h gen_alloc.h case.h byte.h str.h \
 dns.h iopause.h auto-iopause.h taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compile.sh
	$C  -c dns_ipq6.c
dns_ipq64.o: dns_ipq64.c stralloc.h gen_alloc.h case.h byte.h str.h \
 dns.h iopause.h auto-iopause.h taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compile.sh
	$C  -c dns_ipq64.c
dns_packet.o: dns_packet.c error.h dns.h stralloc.h gen_alloc.h \
 iopause.h auto-iopause.h taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compile.sh
	$C  -c dns_packet.c
dns_random.o: dns_random.c dns.h stralloc.h gen_alloc.h iopause.h \
 auto-iopause.h taia.h tai.h uint64.h typesize.h auto-typesize.h \
 uint32.h auto-compile.sh
	$C  -c dns_random.c
dns_rcip.o: dns_rcip.c taia.h tai.h uint64.h typesize.h \
 auto-typesize.h openreadclose.h stralloc.h gen_alloc.h byte.h ip4.h \
 ip6.h env.h dns.h iopause.h auto-iopause.h auto-compile.sh
	$C  -c dns_rcip.c
dns_rcrw.o: dns_rcrw.c taia.h tai.h uint64.h typesize.h \
 auto-typesize.h env.h byte.h str.h openreadclose.h stralloc.h \
 gen_alloc.h dns.h iopause.h auto-iopause.h auto-compile.sh
	$C  -c dns_rcrw.c
dns_resolve.o: dns_resolve.c iopause.h auto-iopause.h taia.h tai.h \
 uint64.h typesize.h auto-typesize.h byte.h dns.h stralloc.h \
 gen_alloc.h ip6.h auto-compile.sh
	$C  -c dns_resolve.c
dns_sortip.o: dns_sortip.c byte.h dns.h stralloc.h gen_alloc.h \
 iopause.h auto-iopause.h taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compile.sh
	$C  -c dns_sortip.c
dns_sortip6.o: dns_sortip6.c byte.h dns.h stralloc.h gen_alloc.h \
 iopause.h auto-iopause.h taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compile.sh
	$C  -c dns_sortip6.c
dns_transmit.o: dns_transmit.c socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h alloc.h error.h byte.h \
 dns.h stralloc.h gen_alloc.h iopause.h auto-iopause.h taia.h tai.h \
 uint64.h ip6.h auto-compile.sh
	$C  -c dns_transmit.c
env_get.o: env_get.c env.h auto-compilew.sh
	$W  -c env_get.c
eof_or_error.o: eof_or_error.c bailout.h buffer.h ftpcopy.h stralloc.h \
 gen_alloc.h attributes.h auto-compilew.sh
	$W  -c eof_or_error.c
error.o: error.c error.h auto-compilew.sh
	$W  -c error.c
error_str.o: error_str.c error.h auto-compilew.sh
	$W  -c error_str.c
fmt_uint0.o: fmt_uint0.c gen_fmt.h fmt.h auto-compilew.sh
	$W  -c fmt_uint0.c
fmt_uint64.o: fmt_uint64.c gen_fmt.h fmt.h fs64.h uint64.h typesize.h \
 auto-typesize.h auto-compilew.sh
	$W  -c fmt_uint64.c
fmt_ulong.o: fmt_ulong.c gen_fmt.h fmt.h auto-compilew.sh
	$W  -c fmt_ulong.c
fmt_xlong.o: fmt_xlong.c gen_fmt.h fmt.h auto-compilew.sh
	$W  -c fmt_xlong.c
ftp_read_lis.o: ftp_read_lis.c stralloc.h gen_alloc.h buffer.h getln.h \
 timeoutio.h taia.h tai.h uint64.h typesize.h auto-typesize.h \
 iopause.h auto-iopause.h error.h ftplib.h readwrite.h str.h case.h \
 ftpcopy.h attributes.h auto-compilew.sh
	$W  -c ftp_read_lis.c
ftpcopy.o: ftpcopy.c attributes.h ftpparse.h tai.h uint64.h typesize.h \
 auto-typesize.h buffer.h stralloc.h gen_alloc.h scan.h ip4.h alloc.h \
 byte.h getln.h ftplib.h strhash.h uint32.h fmt.h fs64.h uogetopt.h \
 uotime.h uo_wildmat.h urlparse.h timeoutio.h taia.h iopause.h \
 auto-iopause.h error.h ftpcopy.h bailout.h str.h open.h readwrite.h \
 close.h nowarn.h get_cwd.h api_futimes.h api_utimes.h case.h mdtm.h \
 api_dir.h mysleep.h socket.h uint16.h auto-have_ipv6.h ssort.h env.h auto-compilew.sh
	$W  -c ftpcopy.c
ftplib.o: ftplib.c buffer.h stralloc.h gen_alloc.h ip4.h scan.h \
 getln.h ftplib.h host_connect.h str.h fmt.h byte.h auto-compilew.sh
	$W  -c ftplib.c
ftpls.o: ftpls.c attributes.h stralloc.h gen_alloc.h ftpparse.h tai.h \
 uint64.h typesize.h auto-typesize.h buffer.h ftplib.h alloc.h ip4.h \
 uogetopt.h uotime.h urlparse.h iopause.h auto-iopause.h taia.h \
 getln.h fmt.h str.h error.h ftpcopy.h bailout.h close.h readwrite.h \
 sort_it.h strhash.h uint32.h socket.h uint16.h auto-have_ipv6.h env.h \
 fs64.h auto-compilew.sh
	$W  -c ftpls.c
ftpparse.o: ftpparse.c ftpparse.h tai.h uint64.h typesize.h \
 auto-typesize.h bailout.h buffer.h str.h case.h utcdate2tai.h auto-compilew.sh
	$W  -c ftpparse.c
gen_alloc_ady.o: gen_alloc_ady.c alloc.h gen_alloci.h auto-compilew.sh
	$W  -c gen_alloc_ady.c
gen_alloc_end.o: gen_alloc_end.c gen_alloci.h byte.h auto-compilew.sh
	$W  -c gen_alloc_end.c
gen_alloc_lus.o: gen_alloc_lus.c gen_alloci.h auto-compilew.sh
	$W  -c gen_alloc_lus.c
get_cwd.o: get_cwd.c alloc.h error.h stralloc.h gen_alloc.h byte.h \
 str.h get_cwd.h auto-compilew.sh
	$W  -c get_cwd.c
getln.o: getln.c byte.h getln.h buffer.h stralloc.h gen_alloc.h auto-compilew.sh
	$W  -c getln.c
host_connect4.o: host_connect4.c stralloc.h gen_alloc.h scan.h ip4.h \
 socket.h uint16.h typesize.h auto-typesize.h uint32.h \
 auto-have_ipv6.h error.h host_connect.h timeoutconn.h str.h dns.h \
 iopause.h auto-iopause.h taia.h tai.h uint64.h byte.h bailout.h \
 buffer.h auto-compilew.sh
	$W  -c host_connect4.c
host_connect64.o: host_connect64.c stralloc.h gen_alloc.h scan.h ip6.h \
 ip4.h socket.h uint16.h typesize.h auto-typesize.h uint32.h \
 auto-have_ipv6.h error.h host_connect.h timeoutconn.h str.h dns.h \
 iopause.h auto-iopause.h taia.h tai.h uint64.h byte.h bailout.h \
 buffer.h close.h socket_if.h auto-compilew.sh
	$W  -c host_connect64.c
inq_winsize.o: inq_winsize.c sig.h ftpcopy.h buffer.h stralloc.h \
 gen_alloc.h attributes.h auto-compilew.sh
	$W  -c inq_winsize.c
iopause.o: iopause.c taia.h tai.h uint64.h typesize.h auto-typesize.h \
 iopause.h auto-iopause.h auto-compilew.sh
	$W  -c iopause.c
ip4_constants.o: ip4_constants.c ip4.h auto-compilew.sh
	$W  -c ip4_constants.c
ip4_fmt.o: ip4_fmt.c fmt.h ip4.h auto-compilew.sh
	$W  -c ip4_fmt.c
ip4_scan.o: ip4_scan.c ip4.h scan.h auto-compile.sh
	$C  -c ip4_scan.c
ip6_constants.o: ip6_constants.c ip6.h auto-compilew.sh
	$W  -c ip6_constants.c
ip6_fmt.o: ip6_fmt.c fmt.h byte.h ip4.h ip6.h auto-compilew.sh
	$W  -c ip6_fmt.c
ip6_scan.o: ip6_scan.c scan.h ip4.h ip6.h byte.h auto-compilew.sh
	$W  -c ip6_scan.c
mdtm.o: mdtm.c ftpparse.h tai.h uint64.h typesize.h auto-typesize.h \
 buffer.h stralloc.h gen_alloc.h ftplib.h ftpcopy.h attributes.h \
 mdtm.h bailout.h error.h utcdate2tai.h auto-compilew.sh
	$W  -c mdtm.c
mysleep.o: mysleep.c iopause.h auto-iopause.h taia.h tai.h uint64.h \
 typesize.h auto-typesize.h mysleep.h auto-compilew.sh
	$W  -c mysleep.c
ndelay_off.o: ndelay_off.c ndelay.h auto-compilew.sh
	$W  -c ndelay_off.c
ndelay_on.o: ndelay_on.c ndelay.h auto-compilew.sh
	$W  -c ndelay_on.c
open_append.o: open_append.c open.h auto-compilew.sh
	$W  -c open_append.c
open_excl.o: open_excl.c open.h auto-compilew.sh
	$W  -c open_excl.c
open_read.o: open_read.c open.h auto-compilew.sh
	$W  -c open_read.c
openreadclose.o: openreadclose.c error.h open.h readclose.h stralloc.h \
 gen_alloc.h openreadclose.h auto-compilew.sh
	$W  -c openreadclose.c
readclose.o: readclose.c readclose.h stralloc.h gen_alloc.h auto-compilew.sh
	$W  -c readclose.c
readclose_app.o: readclose_app.c readwrite.h error.h readclose.h \
 stralloc.h gen_alloc.h close.h auto-compilew.sh
	$W  -c readclose_app.c
scan_long.o: scan_long.c gen_scan.h scan.h case.h auto-compilew.sh
	$W  -c scan_long.c
scan_sign.o: scan_sign.c scan.h auto-compilew.sh
	$W  -c scan_sign.c
scan_ulong.o: scan_ulong.c gen_scan.h scan.h case.h auto-compilew.sh
	$W  -c scan_ulong.c
scan_xlong.o: scan_xlong.c gen_scan.h scan.h case.h auto-compilew.sh
	$W  -c scan_xlong.c
sig.o: sig.c sig.h auto-compile.sh
	$C  -c sig.c
sig_catch.o: sig_catch.c sig.h auto-compile.sh
	$C  -c sig_catch.c
socket_bind.o: socket_bind.c byte.h socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h auto-compilew.sh
	$W  -c socket_bind.c
socket_bind6.o: socket_bind6.c byte.h socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h error.h auto-compilew.sh
	$W  -c socket_bind6.c
socket_bind64.o: socket_bind64.c socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h error.h auto-compilew.sh
	$W  -c socket_bind64.c
socket_conn.o: socket_conn.c byte.h socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h auto-compilew.sh
	$W  -c socket_conn.c
socket_conn6.o: socket_conn6.c byte.h socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h error.h auto-compilew.sh
	$W  -c socket_conn6.c
socket_conn64.o: socket_conn64.c byte.h socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h error.h ip6.h ip4.h auto-compilew.sh
	$W  -c socket_conn64.c
socket_connt.o: socket_connt.c readwrite.h byte.h socket.h uint16.h \
 typesize.h auto-typesize.h uint32.h auto-have_ipv6.h auto-socklen_t.h auto-compilew.sh
	$W  -c socket_connt.c
socket_family.o: socket_family.c socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h auto-compilew.sh
	$W  -c socket_family.c
socket_flag.o: socket_flag.c socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h auto-compilew.sh
	$W  -c socket_flag.c
socket_gifid.o: socket_gifid.c socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h socket_if.h stralloc.h \
 gen_alloc.h auto-compilew.sh
	$W  -c socket_gifid.c
socket_gifna.o: socket_gifna.c socket_if.h stralloc.h gen_alloc.h \
 uint32.h typesize.h auto-typesize.h auto-compilew.sh
	$W  -c socket_gifna.c
socket_htons.o: socket_htons.c socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h auto-compilew.sh
	$W  -c socket_htons.c
socket_ntohs.o: socket_ntohs.c socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h auto-compilew.sh
	$W  -c socket_ntohs.c
socket_remote6.o: socket_remote6.c byte.h socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h ip6.h error.h auto-compilew.sh
	$W  -c socket_remote6.c
socket_tcp.o: socket_tcp.c ndelay.h socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h auto-compilew.sh
	$W  -c socket_tcp.c
socket_tcp6.o: socket_tcp6.c ndelay.h socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h error.h auto-compilew.sh
	$W  -c socket_tcp6.c
socket_tcp64.o: socket_tcp64.c socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h error.h auto-compilew.sh
	$W  -c socket_tcp64.c
socket_udp.o: socket_udp.c ndelay.h socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h auto-compilew.sh
	$W  -c socket_udp.c
socket_udp6.o: socket_udp6.c ndelay.h socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h error.h auto-compilew.sh
	$W  -c socket_udp6.c
socket_udp64.o: socket_udp64.c socket.h uint16.h typesize.h \
 auto-typesize.h uint32.h auto-have_ipv6.h error.h auto-compilew.sh
	$W  -c socket_udp64.c
sockrecbuf.o: sockrecbuf.c ftpcopy.h buffer.h stralloc.h gen_alloc.h \
 attributes.h auto-compilew.sh
	$W  -c sockrecbuf.c
sort_it.o: sort_it.c ssort.h uint32.h typesize.h auto-typesize.h \
 ftpparse.h tai.h uint64.h sort_it.h byte.h auto-compilew.sh
	$W  -c sort_it.c
ssort.o: ssort.c ssort.h uint32.h typesize.h auto-typesize.h alloc.h \
 byte.h auto-compilew.sh
	$W  -c ssort.c
str_chr.o: str_chr.c str.h auto-compilew.sh
	$W  -c str_chr.c
str_diff.o: str_diff.c str.h auto-compilew.sh
	$W  -c str_diff.c
str_len.o: str_len.c str.h auto-compilew.sh
	$W  -c str_len.c
str_rchr.o: str_rchr.c str.h auto-compilew.sh
	$W  -c str_rchr.c
str_start.o: str_start.c str.h auto-compilew.sh
	$W  -c str_start.c
stralloc_cat.o: stralloc_cat.c stralloc.h gen_alloc.h auto-compilew.sh
	$W  -c stralloc_cat.c
stralloc_catb.o: stralloc_catb.c stralloc.h gen_alloc.h byte.h auto-compilew.sh
	$W  -c stralloc_catb.c
stralloc_cats.o: stralloc_cats.c str.h stralloc.h gen_alloc.h auto-compilew.sh
	$W  -c stralloc_cats.c
stralloc_copy.o: stralloc_copy.c stralloc.h gen_alloc.h auto-compilew.sh
	$W  -c stralloc_copy.c
stralloc_eady.o: stralloc_eady.c stralloc.h gen_alloc.h gen_alloci.h auto-compilew.sh
	$W  -c stralloc_eady.c
stralloc_free.o: stralloc_free.c stralloc.h gen_alloc.h alloc.h auto-compilew.sh
	$W  -c stralloc_free.c
stralloc_opyb.o: stralloc_opyb.c stralloc.h gen_alloc.h byte.h auto-compilew.sh
	$W  -c stralloc_opyb.c
stralloc_opys.o: stralloc_opys.c str.h stralloc.h gen_alloc.h auto-compilew.sh
	$W  -c stralloc_opys.c
stralloc_pend.o: stralloc_pend.c stralloc.h gen_alloc.h gen_alloci.h auto-compilew.sh
	$W  -c stralloc_pend.c
stralloc_plus.o: stralloc_plus.c stralloc.h gen_alloc.h gen_alloci.h auto-compilew.sh
	$W  -c stralloc_plus.c
strhash_crea.o: strhash_crea.c strhashi.h uint32.h typesize.h \
 auto-typesize.h strhash.h auto-compilew.sh
	$W  -c strhash_crea.c
strhash_dest.o: strhash_dest.c strhashi.h uint32.h typesize.h \
 auto-typesize.h strhash.h auto-compilew.sh
	$W  -c strhash_dest.c
strhash_ente.o: strhash_ente.c strhashi.h uint32.h typesize.h \
 auto-typesize.h strhash.h auto-compilew.sh
	$W  -c strhash_ente.c
strhash_get.o: strhash_get.c strhashi.h uint32.h typesize.h \
 auto-typesize.h auto-compilew.sh
	$W  -c strhash_get.c
strhash_hash.o: strhash_hash.c strhashi.h uint32.h typesize.h \
 auto-typesize.h strhash.h auto-compilew.sh
	$W  -c strhash_hash.c
strhash_look.o: strhash_look.c strhashi.h uint32.h typesize.h \
 auto-typesize.h strhash.h auto-compilew.sh
	$W  -c strhash_look.c
tai_add.o: tai_add.c tai.h uint64.h typesize.h auto-typesize.h auto-compilew.sh
	$W  -c tai_add.c
tai_now.o: tai_now.c tai.h uint64.h typesize.h auto-typesize.h auto-compile.sh
	$C  -c tai_now.c
tai_pack.o: tai_pack.c tai.h uint64.h typesize.h auto-typesize.h \
 uint32.h auto-compilew.sh
	$W  -c tai_pack.c
tai_sub.o: tai_sub.c tai.h uint64.h typesize.h auto-typesize.h auto-compilew.sh
	$W  -c tai_sub.c
tai_uint.o: tai_uint.c tai.h uint64.h typesize.h auto-typesize.h auto-compilew.sh
	$W  -c tai_uint.c
taia_add.o: taia_add.c taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compilew.sh
	$W  -c taia_add.c
taia_approx.o: taia_approx.c taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compilew.sh
	$W  -c taia_approx.c
taia_frac.o: taia_frac.c taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compilew.sh
	$W  -c taia_frac.c
taia_half.o: taia_half.c taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compile.sh
	$C  -c taia_half.c
taia_less.o: taia_less.c taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compilew.sh
	$W  -c taia_less.c
taia_now.o: taia_now.c taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compilew.sh
	$W  -c taia_now.c
taia_pack.o: taia_pack.c taia.h tai.h uint64.h typesize.h \
 auto-typesize.h uint32.h auto-compilew.sh
	$W  -c taia_pack.c
taia_sub.o: taia_sub.c taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compilew.sh
	$W  -c taia_sub.c
taia_uint.o: taia_uint.c taia.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compilew.sh
	$W  -c taia_uint.c
timeoutconn.o: timeoutconn.c error.h timeoutconn.h uint16.h typesize.h \
 auto-typesize.h uint32.h socket.h auto-have_ipv6.h auto-compilew.sh
	$W  -c timeoutconn.c
timeoutconn6.o: timeoutconn6.c error.h timeoutconn.h uint16.h \
 typesize.h auto-typesize.h uint32.h socket.h auto-have_ipv6.h auto-compilew.sh
	$W  -c timeoutconn6.c
toconn_common.o: toconn_common.c error.h iopause.h auto-iopause.h \
 taia.h tai.h uint64.h typesize.h auto-typesize.h timeoutconn.h \
 uint16.h uint32.h ndelay.h socket.h auto-have_ipv6.h close.h auto-compilew.sh
	$W  -c toconn_common.c
uint16_pack.o: uint16_pack.c uint16.h typesize.h auto-typesize.h auto-compilew.sh
	$W  -c uint16_pack.c
uint16_unpack.o: uint16_unpack.c uint16.h typesize.h auto-typesize.h auto-compilew.sh
	$W  -c uint16_unpack.c
uint32_pack.o: uint32_pack.c uint32.h typesize.h auto-typesize.h auto-compilew.sh
	$W  -c uint32_pack.c
uint32_unpack.o: uint32_unpack.c uint32.h typesize.h auto-typesize.h auto-compilew.sh
	$W  -c uint32_unpack.c
uo_now.o: uo_now.c uotime.h auto-compilew.sh
	$W  -c uo_now.c
uo_sec702dt.o: uo_sec702dt.c uotime.h auto-compilew.sh
	$W  -c uo_sec702dt.c
uo_wildmat.o: uo_wildmat.c uo_wildmat.h auto-compilew.sh
	$W  -c uo_wildmat.c
uogetopt.o: uogetopt.c readwrite.h str.h env.h scan.h uogetopt.h \
 attributes.h auto-compilew.sh
	$W  -c uogetopt.c
urlparse.o: urlparse.c stralloc.h gen_alloc.h urlparse.h str.h byte.h auto-compilew.sh
	$W  -c urlparse.c
utcdate2tai.o: utcdate2tai.c utcdate2tai.h tai.h uint64.h typesize.h \
 auto-typesize.h auto-compilew.sh
	$W  -c utcdate2tai.c
warn_broken.o: warn_broken.c ftpcopy.h buffer.h stralloc.h gen_alloc.h \
 attributes.h bailout.h auto-compilew.sh
	$W  -c warn_broken.c
yyyy_mm_dd.o: yyyy_mm_dd.c uotime.h fmt.h auto-compilew.sh
	$W  -c yyyy_mm_dd.c
rts check: rts-clean  rts-resolve 
rts-clean:
	rm -f rts-failures 
rts-resolve: 
	@if test -f rts-failures ; then echo The following tests failed: ; \
cat rts-failures ; exit 1; fi 
.PRECIOUS: Makefile
remake: clean
	rm -f auto-compile.sh auto-link.sh auto-compilew.sh auto-makelib.sh
packageinfo: 
	@echo version="$(VERSION)"
	@echo package="$(PACKAGE)"
	@echo class="$(CLASS)"

auto-compile.sh auto-compilew.sh auto-makelib.sh auto-link.sh \
auto-systype.lfs: guess-compiler.sh auto-compiler-config
auto-compiler-config: auto-compiler-config.stamp
auto-config: force
	@( for i in conf-cc conf-ld conf-ldflags conf-cflags conf-cflagsw \
	  conf-ar conf-ranlib conf-libs auto-compile.sh auto-compilew.sh \
	  auto-link.sh auto-makelib.sh ; do \
	  echo $$i ; if test -f $$i ; then cat $$i ; fi ;  \
	done ) >$@.t 
	@mv $@.t $@
auto-compiler-config.stamp: auto-config
	@if cmp auto-config $@ ; then : ; else \
	  echo configuration has changed ; \
	  DEFS='$(DEFS)' INCLUDES='$(INCLUDES)' \
	  PREMAKE_DEFS='$(PREMAKE_DEFS)' \
	  sh guess-compiler.sh ; \
	  rm auto-config ; \
	  $(MYMAKE) auto-config && mv auto-config $@ ; \
	fi 

maintainer-clean: distclean
	rm -f Makefile $(MAINTAINER_CLEANFILES)
distclean: clean
	rm -f $(DISTCLEANFILES) auto-dummy # to avoid "no arguments" error
clean spotless: mostlyclean
	rm -f $(TARGETS) auto-*
	rm -rf deps
mostlyclean:
	rm -f *.o *.a $(CLEANFILES)

NEWS-check:
	@if sed 1q NEWS | grep -e "$(VERSION)" > /dev/null; then :; else \
		echo "NEWS not updated; not releasing" 1>&2; \
		exit 1;                                   \
	fi
	@if grep -e "$(VERSION)" ChangeLog > /dev/null; then :; else \
		echo "ChangeLog not updated; not releasing" 1>&2; \
		exit 1;                                   \
	fi
dist:
	rm -f $(PREMAKE_DIST)
	package
bk-dist: NEWS-check
	bk tag `echo "Release-$(VERSION)" | sed 's/\./-/g'`
	$(MYMAKE) dist
gpg-dist: dist
	gpg -b --armor $(PREMAKE_DIST)
force:	

auto-systype: auto-typesize.h $(EXTRA_SYSTYPE) $(PREMAKE_EXTRA_SYSTYPE)
	rm -f $@.t
	@echo  >>$@.t
	@echo "PACKAGE: $(PACKAGE) $(VERSION)" >>$@.t
	@echo "REALNAME: $(REALNAME)" >>$@.t
	@echo "uname-a:" `uname -a` >>$@.t
	@echo "uname-s:" `uname -s` >>$@.t
	@echo "uname-r:" `uname -r` >>$@.t
	@echo "uname-v:" `uname -v` >>$@.t
	@echo "uname-m:" `uname -m` >>$@.t
	@echo "linux-ld.so:" `ls /lib/ld-*.so` >>$@.t
	@echo "linux-libc.so:" `ls /lib/libc-*.so` >>$@.t
	cat auto-typesize.h >>$@.t
	if test "x$(PREMAKE_EXTRA_SYSTYPE)$(EXTRA_SYSTYPE)" = x ; then true ; else \
	  grep -h systype-info $(PREMAKE_EXTRA_SYSTYPE) $(EXTRA_SYSTYPE) >>$@.t \
	      || exit 1 ; \
	fi
	mv $@.t $@

check: docheck check.exp ftpparse.o utcdate2tai.o ftpcopy ftpls
	sh docheck 2>&1 | cat -v \
	| sed "s,`env - pwd`/tmp.check/,%,g" \
	| tee check.out | diff -u check.exp -
