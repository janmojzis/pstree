/*
Jan Mojzis
Public domain.
20111121
*/

/* tested on OpenBSD, FreeBSD, NetBSD */

#include "proc.h"

#if defined  PROCTYPE_KVMOPENBSD || PROCTYPE_KVMFREEBSD || PROCTYPE_KVMNETBSD

#include <sys/param.h>
#include <sys/user.h>
#include <sys/sysctl.h>
#include <sys/proc.h>
#include <stdlib.h>
#include <fcntl.h>
#include <kvm.h>

#include "stralloc.h"

int proc_add_thread(const char *n, long long pid, long long tid) {

    proc_entry *new;

    if (tid < 0) return 0;

    /* allocate memory for new process */
    new = proc_new();
    if (!new) return -1;

    if (!stralloc_copys(&(new->name), "{")) return -1;
    if (!stralloc_cats(&(new->name), n)) return -1;
    if (!stralloc_cats(&(new->name), "}")) return -1;

    new->fakepid = tid;
    new->fakepid <<= 32;
    new->fakepid += pid;
    new->fakeppid = pid;

    /* add to tree */
    if (!ctx->first) ctx->first = new;
    if (ctx->last) ctx->last->next = new;
    ctx->last = new;

    return 0;
}

int proc_add(const char *n, long long pid, long long ppid){

    proc_entry *new;
    stralloc *name;

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

char errbuf[4096];

int proc_get(void){

#if defined  PROCTYPE_KVMOPENBSD || PROCTYPE_KVMFREEBSD
    struct kinfo_proc *kp;
#endif
#ifdef PROCTYPE_KVMNETBSD
    struct kinfo_proc2 *kp;
#endif
    kvm_t *kd;
    int nentries, i;
    proc_entry *t;
    int flagslave;

    kd = kvm_openfiles(0, 0, 0, O_RDONLY, errbuf);
    if (!kd) return -1;

#if defined PROCTYPE_KVMOPENBSD
    kp = kvm_getprocs(kd, KERN_PROC_ALL | KERN_PROC_SHOW_THREADS | KERN_PROC_KTHREAD, 0, sizeof(*kp), &nentries);
#endif
#ifdef PROCTYPE_KVMFREEBSD
    kp = kvm_getprocs(kd, KERN_PROC_ALL, 0, &nentries);
#endif
#ifdef PROCTYPE_KVMNETBSD
    kp = kvm_getproc2(kd, KERN_PROC_ALL, 0, sizeof(*kp), &nentries);
#endif

    if (!kp) return -1;

    for (i = 0; i < nentries; i++) {
#ifdef  PROCTYPE_KVMOPENBSD
        if (kp[i].p_tid < 0) continue;
#ifndef THREAD_PID_OFFSET
        if (kp[i].p_flag & P_THREAD) {
#else
        if (kp[i].p_tid == kp[i].p_pid + THREAD_PID_OFFSET) {
#endif
            if (proc_add(kp[i].p_comm, kp[i].p_pid, kp[i].p_ppid) == -1) return -1;
        }
        else { 
            if (proc_add_thread(kp[i].p_comm, kp[i].p_pid, kp[i].p_tid) == -1) return -1;
        }
#endif
#ifdef  PROCTYPE_KVMNETBSD
        if (proc_add(kp[i].p_comm, kp[i].p_pid, kp[i].p_ppid) == -1) return -1;
#endif
#ifdef PROCTYPE_KVMFREEBSD
        if (kp[i].ki_numthreads == 1) {
            if (proc_add(kp[i].ki_comm, kp[i].ki_pid, kp[i].ki_ppid) == -1) return -1;
        }
        else {
            flagslave = 0;
            for (t = ctx->first; t; t = t->next) {
                if (t->fakepid == kp[i].ki_pid && t->fakeppid == kp[i].ki_ppid) { flagslave = 1; break; }
            }
            if (flagslave) {
                if (proc_add_thread(kp[i].ki_tdname, kp[i].ki_pid, kp[i].ki_tid) == -1) return -1;
            }
            else {
                if (proc_add(kp[i].ki_comm, kp[i].ki_pid, kp[i].ki_ppid) == -1) return -1;
                if (proc_add_thread(kp[i].ki_tdname, kp[i].ki_pid, kp[i].ki_tid) == -1) return -1;
            }
        }
#endif
    }
    kvm_close(kd);
    return 0;
}

#endif  /* PROCTYPE_KVMOPENBSD || PROCTYPE_KVMFREEBSD */
