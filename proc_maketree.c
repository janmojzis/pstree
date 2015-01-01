/*
Jan Mojzis
Public domain.
20091019
*/

#include "proc.h"
#include "alloc.h"
#include "byte.h"
#include "gen_allocdefs.h"
#include "error.h"


#define min(x, y) ((x) < (y) ? (x) : (y))
static void sort(proc_entry **pe, unsigned int len){

    unsigned int i, j;
    stralloc *a, *b;
    proc_entry *tmp;

    if (len <= 1) return;
    for(i = 0; i < len - 1; ++i){
        for(j = len - 1; j > i; --j){
            a = &pe[j-1]->name;
            b = &pe[j]->name;
            /* compare */
            if (byte_diff(a->s, min(a->len, b->len), b->s) > 0){
                /* swap */
                tmp     = pe[j-1];
                pe[j-1] = pe[j];
                pe[j]   = tmp;
            }
        }
    }
}

GEN_ALLOC_readyplus(procchild_alloc,proc_entry *,s,len,a,i,n,x,14,procchild_readyplus)
GEN_ALLOC_append(procchild_alloc,proc_entry *,s,len,a,i,n,x,14,procchild_readyplus,procchild_append)

int proc_maketree(void){

    proc_entry *t;
    proc_entry *n;
    int m = 2;
    int pid;

    if (!ctx->first){errno = error_noent; return -1;}

    /* create tree */
    for(t = ctx->first; t; t = t->next){ 
        pid = t->fakepid & 0xffffffff;
        if (pid < m){
            m = pid;
            ctx->master = t;
        }
        for(n = t->next; n; n = n->next){ 
            if (t->fakepid == n->fakeppid){
                if (!procchild_append(&t->childs, (const proc_entry **)&n)) return -1;
                n->parent = t;
            }
            if (n->fakepid == t->fakeppid){
                if (!procchild_append(&n->childs, (const proc_entry **)&t)) return -1;
                t->parent = n;
            }
        }
    }

    /* sort childs */
    for(t = ctx->first;t; t = t->next){
        if (t->count == 0){
            sort(t->childs.s, t->childs.len); 
            t->count = 1;
        }
    }

    return 0;
}

