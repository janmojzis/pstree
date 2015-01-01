/*
Jan Mojzis
Public domain.
20091020
*/

/* tested on sunos, aix */

#include "proc.h"

#ifdef PROCTYPE_PSINFO

#include "stralloc.h"
#include "openreadclose.h"
#include "error.h"
#include "scan.h"

static stralloc taskname = {0};
static stralloc taskdir  = {0};
static int taskppid = -1;

int proc_add_thread(const char *procdir, const char *piddir){

    unsigned long ul;
    unsigned int i;
    proc_entry *new;
    stralloc *name;

    /* assuming that thread name is same as process name */
    i = scan_ulong(piddir,&ul);
    if (!i) return 0; /* XXX */
    if (ul == 1) return 0; /* master thread */

    /* allocate memory for new process */
    new = proc_new();
    if (!new) return -1;
    name = &(new->name);

    if (!stralloc_copys(name, "{")) return -1;
    if (!stralloc_cat(name, &taskname)) return -1;
    if (!stralloc_cats(name, "}")) return -1;
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

static stralloc buf = {0};
static stralloc fn = {0};

int proc_add(const char *procdir ,const char *piddir){

    psinfo_t *ps;
    lwpsinfo_t *lwps;
    proc_entry *new;
    stralloc *name;

    /* allocate memory for new process */
    new = proc_new();
    if (!new) return -1;
    name = &(new->name);

    /* psinfo filename */
    if (!stralloc_copys(&fn, procdir)) return -1;
    if (!stralloc_copys(&fn, "/")) return -1;
    if (!stralloc_copys(&fn, piddir)) return -1;
    if (!stralloc_cats(&fn,"/psinfo")) return -1;
    if (!stralloc_0(&fn)) return -1;

    /* read */
    if (openreadclose(fn.s, &buf, sizeof(psinfo_t)) <= 0) return -1;

    if (buf.len != sizeof(psinfo_t)) {errno = error_proto; return -1;}
    ps = (psinfo_t *)buf.s;

    if (!stralloc_copys(name, ps->pr_fname)) return -1;
    if (!stralloc_copys(&taskname, ps->pr_fname)) return -1;
    new->fakepid = ps->pr_pid;
    taskppid     = ps->pr_pid;
    new->fakeppid = ps->pr_ppid;

    /* add to tree */
    if (!ctx->first) ctx->first = new;
    if (ctx->last) ctx->last->next = new;
    ctx->last = new;

    /* add tasks */
    if (!stralloc_copys(&taskdir, procdir)) return -1;
    if (!stralloc_cats(&taskdir, "/")) return -1;
    if (!stralloc_cats(&taskdir, piddir)) return -1;
    if (!stralloc_cats(&taskdir,"/lwp")) return -1;
    if (!stralloc_0(&taskdir)) return -1;
    if (proc_read(procdir, taskdir.s, proc_add_thread) == -1) return -1;


  return 0;
}

int proc_get(void){
    return proc_read("/proc", "/proc", proc_add);
}


#endif /* PROCTYPE_PSINFO */
