#ifndef GOGOMILLAN
#define GOGOMILLAN OK

#define TRUE  1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

int _readdir(char **dirs, char **opts);
int getargs(char **argv, char ***dirs, char ***opts);

int countagrs(char **argv, int *dir_qty, int *opt_qty);
int setmemdir(int dir_qty, char ***dir);
int setmemopt(int opt_qty, char ***opt);
int releasemem(char ***dir, char ***opt);

extern int errno;
/**
 * dirent - struct for directory entry
 *
 * @d_ino: inode number
 * @d_off: not an offset; see NOTES
 * @d_reclen: length of this record
 * @d_type: type of file; not supported by all filesystem types
 * @d_name[256]: filename
 */
struct dirent *read;

#endif /* GOGOMILLAN */
