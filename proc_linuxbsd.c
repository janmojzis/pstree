/*
Jan Mojzis
Public domain.
20091020
*/

/* tested on Linux, NetBSD */

#include "proc.h"

#if defined PROCTYPE_LINUX || PROCTYPE_BSD

#include "stralloc.h"
#include "error.h"
#include "scan.h"
#include "openreadclose.h"

static stralloc taskdir = {0};
static stralloc taskname = {0};
static int taskppid = -1;

static stralloc line = {0};
static stralloc fn  = {0};
static stralloc pidstr = {0};
static stralloc ppidstr = {0};


int parsefile(char *fn) {

    int r,i,spaces;

    r = openreadclose(fn, &line, 64);
    if (r <= 0) return -1;

    if (!stralloc_copys(&pidstr,"")) return -1;
    if (!stralloc_copys(&ppidstr,"")) return -1;
    if (!stralloc_copys(&taskname,"")) return -1;

    spaces = 0;
#ifdef PROCTYPE_BSD
    spaces = 1;
#endif
    for (i = 0;i < line.len;++i){
        if (line.s[i] == ' ') {
            ++spaces;
            if (spaces >= 4) break;
        }
        else{
            switch(spaces) {
                case 0:
                    if (!stralloc_append(&pidstr,line.s + i)) return -1;
                    break;
                case 1:
#ifdef PROCTYPE_LINUX
                    if (line.s[i] == '(' || line.s[i] == ')')
                        break;
#endif
                    if (!stralloc_append(&taskname,line.s + i)) return -1;
                    break;
                case 2:
#ifdef PROCTYPE_BSD
                    if (!stralloc_append(&pidstr,line.s + i)) return -1;
#endif
                    break;
                case 3:
                    if (!stralloc_append(&ppidstr,line.s + i)) return -1;
                    break;
            }
        }
    }
    errno = error_proto;
    if (pidstr.len == 0  || pidstr.len > 10) return -1;
    if (ppidstr.len == 0 || ppidstr.len > 10) return -1;

    if (!stralloc_0(&pidstr)) return -1;
    if (!stralloc_0(&ppidstr)) return -1;
    return 0;
}


int proc_add_thread(const char *procdir, const char *piddir){

    unsigned long ul;
    unsigned int i;
    proc_entry *new;

    if (!stralloc_copys(&fn, procdir)) return -1;
    if (!stralloc_cats(&fn, "/")) return -1;
    if (!stralloc_cats(&fn, piddir)) return -1;
    if (!stralloc_cats(&fn,"/stat")) return -1;
#ifdef PROCTYPE_BSD
    if (!stralloc_cats(&fn,"us")) return -1;
#endif
    if (!stralloc_0(&fn)) return -1;

    if (parsefile(fn.s) == -1) return -1;

    i = scan_ulong(piddir,&ul);
    if (!i) return 0; /* XXX */
    if (ul == taskppid) return 0; /* master thread */

    /* allocate memory for new process */
    new = proc_new();
    if (!new) return -1;

    if (!stralloc_copys(&(new->name), "{")) return -1;
    if (!stralloc_cat(&(new->name), &taskname)) return -1;
    if (!stralloc_cats(&(new->name), "}")) return -1;
    new->fakepid = ul;
    new->fakepid <<= 32;
    new->fakepid += taskppid;
    new->fakeppid = taskppid;

    /* add to tree */
    if (!ctx->first) ctx->first = new;
    if (ctx->last) ctx->last->next = new;
    ctx->last = new;

    return 0;
}

int proc_add(const char *procdir ,const char *piddir, int procpid){

    int r,i,spaces;
    unsigned long ul;
    proc_entry *new;

    if (!stralloc_copys(&fn, procdir)) return -1;
    if (!stralloc_cats(&fn, "/")) return -1;
    if (!stralloc_cats(&fn, piddir)) return -1;
    if (!stralloc_cats(&fn,"/stat")) return -1;
#ifdef PROCTYPE_BSD
    if (!stralloc_cats(&fn,"us")) return -1;
#endif
    if (!stralloc_0(&fn)) return -1;

    if (parsefile(fn.s) == -1) return -1;

    /* copy name */
    new = proc_new();
    if (!new) return -1;

    /* copy name */
    if (!stralloc_copy(&(new->name), &taskname)) return -1;

    /* get pid */
    r = scan_ulong(pidstr.s, &ul);
    if (r == 0 || r > 10) return -1;
    new->fakepid = ul;
    taskppid = (int)ul;

    /* get ppid */
    r = scan_ulong(ppidstr.s, &ul);
    if (r == 0 || r > 10) return -1;
    new->fakeppid = ul;

    /* add to tree */
    if (!ctx->first) ctx->first = new;
    if (ctx->last) ctx->last->next = new;
    ctx->last = new;

#ifdef PROCTYPE_LINUX
    /* add tasks */
    if (!stralloc_copys(&taskdir, procdir)) return -1;
    if (!stralloc_cats(&taskdir, "/")) return -1;
    if (!stralloc_cats(&taskdir, piddir)) return -1;
    if (!stralloc_cats(&taskdir,"/task")) return -1;
    if (!stralloc_0(&taskdir)) return -1;
    if (proc_read(procdir, taskdir.s, proc_add_thread) == -1) return -1;
#endif

    errno = 0;
    return 0;
}

int proc_get(void){
    return proc_read("/proc", "/proc", proc_add);
}


#endif /* PROCTYPE_LINUX */
