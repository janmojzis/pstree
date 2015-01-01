/*
Jan Mojzis
Public domain.
20081230
*/

#include "proc.h"
#include "error.h"

int proc_includepid(void){

    proc_entry *t;
    int pid;

    if (!ctx->first) {errno = error_noent; return -1;}
    for(t = ctx->first; t; t = t->next){
        if (t->fakepid != (t->fakepid & 0xffffffff)){
            /* thread */
            pid = (t->fakepid >> 32);
        }
        else{
            /* process */
            pid = t->fakepid & 0xffffffff;
        }
        if (!stralloc_cats(&t->name, "(")) return -1;
        if (!stralloc_catint(&t->name, pid)) return -1;
        if (!stralloc_cats(&t->name, ")")) return -1;
    }
    return 0;
}
