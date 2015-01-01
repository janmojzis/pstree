/*
Jan Mojzis
Public domain.
20111123
*/

#include "proc.h"

#ifdef PROCTYPE_BSDKINFOPROC

#include <stdlib.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/proc.h>

#include "stralloc.h"


int proc_add(const char *n, long long pid, long long ppid){

    proc_entry *new;
    proc_entry *t;
    stralloc *name;

    /* XXX - remove threads */
    for (t = ctx->first; t; t = t->next) {
        if (t->fakepid == pid && t->fakeppid == ppid) return 0;
    }

    /* allocate memory for new process */
    new = proc_new();
    if (!new) return -1;
    name = &(new->name);

    if (!stralloc_copys(name, n)) return -1;
    new->fakepid = pid;
    new->fakeppid = ppid;

    /* add to tree */
    if (!ctx->first) ctx->first = new;
    if (ctx->last) ctx->last->next = new;
    ctx->last = new;

  return 0;
}

int proc_get(void){

    struct kinfo_proc *kp = 0;
    static const int name[] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0 };
    int r;
    size_t length;
    int nentries, i, xi;
    char *xs;

    r = sysctl((int *)name, (sizeof(name) / sizeof(*name)) - 1, 0, &length, 0, 0);
    if (r < 0) return -1;
    nentries = length / sizeof(struct kinfo_proc);

    kp = malloc(length);
    if (!kp) return -1;

    // Get the actual process list
    r = sysctl((int *)name, (sizeof(name) / sizeof(*name)) - 1, kp, &length, 0, 0);
    if (r < 0) { free(kp); return -1; }

    for (i = 0; i < nentries; i++) {
    	if (proc_add(xs=kp[i].kp_proc.p_comm, kp[i].kp_proc.p_pid, xi=kp[i].kp_eproc.e_ppid) == -1) { free(kp); return -1; }
    }
    free(kp);

    return 0;
}

#endif  /* PROCTYPE_BSDKINFOPROC */
