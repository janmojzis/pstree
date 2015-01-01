default: it

alloc.o: \
alloc.h \
error.h \
alloc.c \
compile
	./compile alloc.c

alloc_re.o: \
alloc.h \
byte.h \
alloc_re.c \
compile
	./compile alloc_re.c

buffer_1s.o: \
buffer.h \
buffer_1s.c \
compile
	./compile buffer_1s.c

buffer_2.o: \
buffer.h \
buffer_2.c \
compile
	./compile buffer_2.c

buffer.o: \
buffer.h \
buffer.c \
compile
	./compile buffer.c

buffer_get.o: \
buffer.h \
byte.h \
error.h \
buffer_get.c \
compile
	./compile buffer_get.c

buffer_put.o: \
buffer.h \
byte.h \
error.h \
str.h \
buffer_put.c \
compile
	./compile buffer_put.c

buffer_read.o: \
buffer.h \
buffer_read.c \
compile
	./compile buffer_read.c

buffer_write.o: \
buffer.h \
buffer_write.c \
compile
	./compile buffer_write.c

byte_chr.o: \
byte.h \
byte_chr.c \
compile
	./compile byte_chr.c

byte_copy.o: \
byte.h \
byte_copy.c \
compile
	./compile byte_copy.c

byte_cr.o: \
byte.h \
byte_cr.c \
compile
	./compile byte_cr.c

byte_diff.o: \
byte.h \
byte_diff.c \
compile
	./compile byte_diff.c

byte_zero.o: \
byte.h \
byte_zero.c \
compile
	./compile byte_zero.c

error.o: \
error.h \
error.c \
compile
	./compile error.c

error_str.o: \
error.h \
error_str.c \
compile
	./compile error_str.c

fmt_ulong.o: \
fmt.h \
fmt_ulong.c \
compile
	./compile fmt_ulong.c

getln2.o: \
buffer.h \
byte.h \
gen_alloc.h \
getln.h \
stralloc.h \
getln2.c \
compile
	./compile getln2.c

getln.o: \
buffer.h \
byte.h \
gen_alloc.h \
getln.h \
stralloc.h \
getln.c \
compile
	./compile getln.c

open_read.o: \
open.h \
open_read.c \
compile
	./compile open_read.c

openreadclose.o: \
error.h \
gen_alloc.h \
open.h \
openreadclose.h \
readclose.h \
stralloc.h \
openreadclose.c \
compile
	./compile openreadclose.c

proc_bsdkinfoproc.o: \
gen_alloc.h \
proc.h \
proctype.h \
stralloc.h \
proc_bsdkinfoproc.c \
compile
	./compile proc_bsdkinfoproc.c

proc.o: \
gen_alloc.h \
proc.h \
proctype.h \
stralloc.h \
proc.c \
compile
	./compile proc.c

proc_compact.o: \
byte.h \
gen_alloc.h \
proc.h \
proctype.h \
stralloc.h \
proc_compact.c \
compile
	./compile proc_compact.c

proc_includepid.o: \
error.h \
gen_alloc.h \
proc.h \
proctype.h \
stralloc.h \
proc_includepid.c \
compile
	./compile proc_includepid.c

proc_kvm.o: \
gen_alloc.h \
proc.h \
proctype.h \
stralloc.h \
proc_kvm.c \
compile
	./compile proc_kvm.c

proc_linuxbsd.o: \
error.h \
gen_alloc.h \
openreadclose.h \
proc.h \
proctype.h \
scan.h \
stralloc.h \
proc_linuxbsd.c \
compile
	./compile proc_linuxbsd.c

proc_maketree.o: \
alloc.h \
byte.h \
error.h \
gen_allocdefs.h \
gen_alloc.h \
proc.h \
proctype.h \
stralloc.h \
proc_maketree.c \
compile
	./compile proc_maketree.c

proc_new.o: \
alloc.h \
byte.h \
gen_alloc.h \
proc.h \
proctype.h \
stralloc.h \
proc_new.c \
compile
	./compile proc_new.c

proc_print.o: \
buffer.h \
fmt.h \
gen_alloc.h \
proc.h \
proctype.h \
stralloc.h \
strerr.h \
str.h \
proc_print.c \
compile
	./compile proc_print.c

proc_psinfo.o: \
error.h \
gen_alloc.h \
openreadclose.h \
proc.h \
proctype.h \
scan.h \
stralloc.h \
proc_psinfo.c \
compile
	./compile proc_psinfo.c

proc_read.o: \
direntry.h \
error.h \
gen_alloc.h \
proc.h \
proctype.h \
scan.h \
stralloc.h \
proc_read.c \
compile
	./compile proc_read.c

pstree.o: \
gen_alloc.h \
proc.h \
proctype.h \
sgetopt.h \
stralloc.h \
strerr.h \
subgetopt.h \
pstree.c \
compile
	./compile pstree.c

readclose.o: \
error.h \
gen_alloc.h \
readclose.h \
stralloc.h \
readclose.c \
compile
	./compile readclose.c

scan_ulong.o: \
scan.h \
scan_ulong.c \
compile
	./compile scan_ulong.c

sgetopt.o: \
buffer.h \
sgetopt.h \
subgetopt.h \
sgetopt.c \
compile
	./compile sgetopt.c

stralloc_catb.o: \
byte.h \
gen_alloc.h \
stralloc.h \
stralloc_catb.c \
compile
	./compile stralloc_catb.c

stralloc_cat.o: \
byte.h \
gen_alloc.h \
stralloc.h \
stralloc_cat.c \
compile
	./compile stralloc_cat.c

stralloc_cats.o: \
byte.h \
gen_alloc.h \
stralloc.h \
str.h \
stralloc_cats.c \
compile
	./compile stralloc_cats.c

stralloc_copy.o: \
byte.h \
gen_alloc.h \
stralloc.h \
stralloc_copy.c \
compile
	./compile stralloc_copy.c

stralloc_eady.o: \
alloc.h \
gen_allocdefs.h \
gen_alloc.h \
stralloc.h \
stralloc_eady.c \
compile
	./compile stralloc_eady.c

stralloc_num.o: \
gen_alloc.h \
stralloc.h \
stralloc_num.c \
compile
	./compile stralloc_num.c

stralloc_opyb.o: \
byte.h \
gen_alloc.h \
stralloc.h \
stralloc_opyb.c \
compile
	./compile stralloc_opyb.c

stralloc_opys.o: \
byte.h \
gen_alloc.h \
stralloc.h \
str.h \
stralloc_opys.c \
compile
	./compile stralloc_opys.c

stralloc_pend.o: \
alloc.h \
gen_allocdefs.h \
gen_alloc.h \
stralloc.h \
stralloc_pend.c \
compile
	./compile stralloc_pend.c

strerr_die.o: \
buffer.h \
strerr.h \
strerr_die.c \
compile
	./compile strerr_die.c

strerr_sys.o: \
error.h \
strerr.h \
strerr_sys.c \
compile
	./compile strerr_sys.c

str_len.o: \
str.h \
str_len.c \
compile
	./compile str_len.c

subgetopt.o: \
subgetopt.h \
subgetopt.c \
compile
	./compile subgetopt.c

trylib.o: \
trylib.c \
compile
	./compile trylib.c

it: pstree

load: \
warn-auto.sh conf-ld
	( cat warn-auto.sh; \
	echo 'main="$$1"; shift'; \
	echo exec "`head -1 conf-ld`" \
	'-o "$$main" "$$main".o $${1+"$$@"}' \
	) > load
	chmod 755 load

compile: \
warn-auto.sh conf-cc
	( cat warn-auto.sh; \
	echo exec "`head -1 conf-cc`" '-c $${1+"$$@"}' \
	) > compile
	chmod 755 compile

choose: \
warn-auto.sh choose.sh compile load kvm.lib
	cat warn-auto.sh choose.sh \
        > choose
	chmod 755 choose

makelib: \
warn-auto.sh
	( cat warn-auto.sh; \
	echo 'main="$$1"; shift'; \
	echo 'rm -f "$$main"'; \
	echo 'ar cr "$$main" $${1+"$$@"}'; \
	case "`uname -s | tr '/:[A-Z]' '..[a-z]'`" in \
	sunos-5.*) ;; \
	unix_sv*) ;; \
	irix64-*) ;; \
	irix-*) ;; \
	dgux-*) ;; \
	hp-ux-*) ;; \
	sco*) ;; \
	*) echo 'ranlib "$$main"' ;; \
	esac \
	) > makelib
	chmod 755 makelib

kvm.lib: \
trylib.c compile load
	( ( ./compile trylib.c && \
        ./load trylib -lkvm ) >/dev/null 2>&1 \
        && echo -lkvm || exit 0 ) > kvm.lib
	rm -f trylib.o trylib

direntry.h: \
choose direntry.h-dirent direntry.h-direct
	./choose direntry.h direntry.h-dirent direntry.h-direct

error.h: \
choose error.h-externerrno error.h-includeerrnoh
	./choose error.h error.h-externerrno error.h-includeerrnoh

proctype.h: \
choose proctype.h-procfs proctype.h-sysprocfs proctype.h-bsdkinfoproc proctype.h-kvmopenbsd proctype.h-kvmfreebsd proctype.h-kvmnetbsd proctype.h-bsd proctype.h-linux
	./choose proctype.h proctype.h-procfs proctype.h-sysprocfs proctype.h-bsdkinfoproc proctype.h-kvmopenbsd proctype.h-kvmfreebsd proctype.h-kvmnetbsd proctype.h-bsd proctype.h-linux


buffer.a: \
makelib buffer.o buffer_1s.o buffer_2.o buffer_get.o \
buffer_put.o strerr_die.o strerr_sys.o
	./makelib buffer.a buffer.o buffer_1s.o buffer_2.o \
	buffer_get.o buffer_put.o strerr_die.o \
	strerr_sys.o

byte.a: \
makelib byte_chr.o byte_copy.o byte_diff.o byte_zero.o byte_cr.o \
fmt_ulong.o scan_ulong.o str_len.o
	./makelib byte.a \
        byte_chr.o byte_copy.o byte_diff.o byte_zero.o byte_cr.o \
        fmt_ulong.o scan_ulong.o str_len.o

unix.a: \
makelib buffer_read.o buffer_write.o error.o error_str.o \
open_read.o openreadclose.o readclose.o
	./makelib unix.a buffer_read.o buffer_write.o error.o \
        error_str.o open_read.o openreadclose.o readclose.o


alloc.a: \
makelib alloc.o alloc_re.o getln.o getln2.o \
stralloc_catb.o stralloc_cats.o stralloc_eady.o \
stralloc_num.o stralloc_opyb.o stralloc_opys.o \
stralloc_pend.o stralloc_copy.o stralloc_cat.o
	./makelib alloc.a alloc.o alloc_re.o getln.o getln2.o \
	stralloc_catb.o stralloc_cats.o \
	stralloc_eady.o stralloc_num.o \
	stralloc_opyb.o stralloc_opys.o \
	stralloc_pend.o stralloc_copy.o stralloc_cat.o

getopt.a: \
makelib sgetopt.o subgetopt.o
	./makelib getopt.a sgetopt.o subgetopt.o

proc.a: \
makelib proc.o proc_compact.o proc_read.o proc_new.o \
proc_includepid.o proc_maketree.o proc_print.o proc_kvm.o \
proc_linuxbsd.o proc_psinfo.o proc_bsdkinfoproc.o
	./makelib proc.a proc.o proc_new.o \
	proc_compact.o proc_read.o proc_includepid.o \
	proc_maketree.o proc_print.o proc_kvm.o \
	proc_linuxbsd.o proc_psinfo.o proc_bsdkinfoproc.o

pstree: \
load pstree.o proc.a getopt.a alloc.a buffer.a unix.a byte.a kvm.lib
	./load pstree proc.a getopt.a alloc.a buffer.a unix.a byte.a `cat kvm.lib`

clean:
	rm -f error.h direntry.h proctype.h load compile choose makelib *.o *.a pstree
	rm -rf solaris/usr solaris/MJpstree debian/pstree debian/pstree.* debian/files


install: it
	test -d `head -1 conf-home` || exit 111
	test -d `head -1 conf-home`/bin  || exit 111
	cp pstree `head -1 conf-home`/bin/pstree

uninstall: 
	test -d `head -1 conf-home` || exit 111
	test -d `head -1 conf-home`/bin  || exit 111
	rm  `head -1 conf-home`/bin/pstree

#debian
/usr/bin/dpkg-buildpackage:
	echo "try apt-get install dpkg-dev"
	exit 111

deb: it /usr/bin/dpkg-buildpackage
	dpkg-buildpackage

#solaris
solaris: it /usr/bin/pkgmk
	test -d solaris/usr || mkdir solaris/usr
	test -d solaris/usr/sfw || mkdir solaris/usr/sfw
	test -d solaris/usr/sfw/bin || mkdir solaris/usr/sfw/bin
	cp pstree solaris/usr/sfw/bin/
	cd solaris ; pkgmk -a `uname -p` -o -f prototype -r . -d .
	pkgtrans -s solaris MJpstree.pkg

