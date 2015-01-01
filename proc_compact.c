/*
Jan Mojzis
Public domain.
20091019
*/

#include "proc.h"
#include "byte.h"


static int proc_isqualr(proc_entry *a, proc_entry *b){

    unsigned int i;

    if (a->name.len != b->name.len) return 0;
    if (a->childs.len != b->childs.len) return 0;

    if (byte_diff(a->name.s,a->name.len,b->name.s) != 0) return 0;
    for (i = 0; i < a->childs.len; ++i)
        if (proc_isqualr(a->childs.s[i], b->childs.s[i]) == 0) return 0;
    return 1;
}


void proc_compact(void){

    proc_entry *t;
    int i,j;

    if (!ctx->first) return;
    for(t = ctx->first; t; t = t->next){
        if (t->childs.len <= 1) continue;
        for(i = 0; i < t->childs.len; ++i){
            for(j = t->childs.len - 1; j > i; --j){
                if (proc_isqualr(t->childs.s[i], t->childs.s[j])){
                    t->childs.s[i]->count = 0;
                    t->childs.s[j]->count += 1;
                }
            }
        }
    }
    return;
}

