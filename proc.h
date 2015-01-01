/*
 Jan Mojzis
 Public domain.
 20081230
*/

#ifndef _PROC_H____
#define _PROC_H____

#include "stralloc.h"
#include "gen_alloc.h"
#include "proctype.h"


GEN_ALLOC_typedef(procchild_alloc,struct proc_entry *,s,len,a)

typedef struct proc_entry{

  stralloc name;
  /* int pid; */
  long long fakepid;
  long long fakeppid;

  /* unsorted tree */
  struct proc_entry *next;

  /* sorted */
  struct proc_entry *parent;
  procchild_alloc childs;

  /* for printing */
  unsigned short int count;

} proc_entry;

typedef struct proc_ctx{

  proc_entry *first;
  proc_entry *last;
  proc_entry *master;

} proc_ctx;

extern proc_ctx *ctx;


/* proc_sysdep.c */
extern int proc_get(void);
/* extern int proc_parse(proc_ctx *, stralloc *, stralloc *, int *, int *); */

extern void proc_print(void);
extern int proc_maketree(void);
extern int proc_includepid(void);
extern void proc_compact(void);
extern int proc_read(const char *rootdir, const char *procdir, int (*callback)());
extern proc_entry *proc_new(void);


#endif
