/*
Jan Mojzis
Public domain.
20081230
*/

#include "fmt.h"
#include "buffer.h"
#include "str.h"
#include "stralloc.h"
#include "strerr.h"
#include "proc.h"

extern char *fatal;

void die_print(void){strerr_die2sys(111,fatal,"unable to print process tree: ");}


static stralloc line = {0};

static unsigned int line_len(proc_entry *t){

    proc_entry *n;
    unsigned int i = 0;
    char strnum[FMT_ULONG]; 

    n = t;
    for(;;){
        if (n->count > 1){
            i+=fmt_ulong(strnum, n->count) + 2;
        }
        if (!n->parent){
            i+=n->name.len + 1;
            break;
        }
        else{
            i+=n->name.len + 3;
        }
        n = n->parent;
    }

    return i;
}

static void flush(void){
    if (buffer_flush(buffer_1small) == -1) die_print();
}

static void put(const char *buf, unsigned int len){
    if (buffer_put(buffer_1small, buf, len) == -1) die_print();
    while(len--){
        if (!stralloc_append(&line," ")) die_print();
    }
}

static void put_str(const char *str){
    put(str, str_len(str));
    return;
}

static void put_num(unsigned int num){
    unsigned int i;
    char strnum[FMT_ULONG];
    i = fmt_ulong(strnum, num);
    put(strnum, i);
    return;
}

static void putx(const char *str){

    if (buffer_put(buffer_1small, str, 1) == -1) die_print();
    if (!stralloc_append(&line,"|")) die_print();
    return;
}


static void put_newline(proc_entry *t){
    unsigned int l;
    put("\n",1);
    l = line_len(t);
    if (line.len < l) die_print(); /* XXX */
    line.len = l;
    if (buffer_put(buffer_1small, line.s, line.len) == -1) die_print();
    return;
}


static void put_sep(proc_entry *t, proc_entry *s, int level){

    unsigned int i;
    int isfirst = 0;
    int islast  = 0;

    /* last */
    for (i = t->childs.len - 1; i >= 0; --i){
        if (t->childs.s[i]->count == 0) continue;
        if (t->childs.s[i] == s) {islast = 1; break;}
        break;
    }

    /* first */
    for(i = 0; i < t->childs.len; ++i){
        if (!t->childs.s[i]->count) continue;
        if (t->childs.s[i] == s) {isfirst = 1; break;}
        break;
    }

    if (isfirst){
        if (islast){
            put_str("---");
            return;
        }
        else{
            put_str("-");putx("+");put_str("-");
            return;
        }
    }

    put_newline(t);

    if (islast){
        put_str("`-");
        return;
    }
    else{
        putx("|");put_str("-");
        return;
    }
}

static void proc_printr(proc_entry *t, int level){

  int i;

  if (t->count == 0){
      return;
  }
  
  if (t->count > 1){
    put_num(t->count);
    put_str("*[");
  }
  put(t->name.s, t->name.len);

  for(i=0;i<t->childs.len; ++i){

    if (t->childs.s[i]->count == 0) continue;
    put_sep(t,t->childs.s[i],level);
    proc_printr(t->childs.s[i], level);

  }

  if (t->count > 1){
    put_str("]");
  }

}

void proc_print(void){

    proc_printr(ctx->master, 0);
    put_str("\n");
    flush();
    return;
}

