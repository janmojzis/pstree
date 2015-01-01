/*
Jan Mojzis
Public domain.
20110310
*/

#include "proc.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "direntry.h"
#include "stralloc.h"
#include "error.h"
#include "scan.h"

int proc_read(const char *rootdir, const char *procdir, int (*callback)()){

    DIR *dir;
    direntry *x;
    struct stat st;
    unsigned long l;
    unsigned int i;


    /* open proc directory */
    if (chdir(procdir) == -1) return -1;
    dir = opendir(procdir);
    if (!dir) return -1;

    /* read proc directory */
    for (;;) {
        errno = 0;
        x = readdir(dir);
        if (!x) break;
        if (x->d_name[0] == '.') continue;
        i = scan_ulong(x->d_name,&l);
        if (i == 0 || i > 10) continue;
        if (stat(x->d_name,&st) == -1) continue;
        if (!S_ISDIR(st.st_mode)) continue;
        if (callback(procdir, x->d_name) == -1) break;
    }
    closedir(dir);
    if (chdir(rootdir) == -1) return -1;
    return 0;
}


