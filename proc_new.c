/*
Jan Mojzis
Public domain.
20091018
*/

#include "proc.h"
#include "alloc.h"
#include "byte.h"

proc_entry *proc_new(void){

    proc_entry *new;

    new = (proc_entry *)alloc(sizeof(proc_entry));
    if (!new) return (proc_entry *)0;
    byte_zero(new, sizeof(proc_entry));
    return new;
}

