/*
Jan Mojzis
Public domain.
20091019
*/

#include <unistd.h>
#include "proc.h"
#include "stralloc.h"
#include "strerr.h"
#include "sgetopt.h"

const char *fatal = "pstree: fatal: ";

void die_get(void){strerr_die2sys(111,fatal,"unable to get process tree: ");}
void die_usage(void){strerr_die1x(100,"usage: pstree [ -p ] [ -h ]\n\t-p\tshow process id\n\t-h\tshow usage\n");}
void die_parse(void){strerr_die2sys(111,fatal,"unable to parse process tree: ");}

int main(int argc, char *argv[]){

    int includepid = 0;
    int opt;

    /* parse arguments */
    while ((opt = getopt(argc,argv,"ph")) != opteof){
        switch(opt) {
            case 'p':
                includepid = 1;
                break;
            case 'h':
                die_usage();
                break;
            default:
                break;
        }
    }

    /* get processes */ 
    if (proc_get() == -1) die_get();

    /* make process tree */
    if (proc_maketree() == -1) die_parse();

    if (includepid){
        /* add pid */
        if (proc_includepid() == -1) die_parse();
    }
    else{
        /* compact tree */
        proc_compact(); 
    }

    /* print tree */
    proc_print();

    _exit(0);
}
