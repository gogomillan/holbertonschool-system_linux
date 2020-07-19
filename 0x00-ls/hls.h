#ifndef GOGOMILLAN
#define GOGOMILLAN OK

#define TRUE  1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

/* main */
int _readdir(char **dirs, char **opts);
int getargs(char **argv, char ***dirs, char ***opts);

/* libgetargs */
int countagrs(char **argv, int *dir_qty, int *opt_qty);
int setmemdir(int dir_qty, char ***dir, char ***tmp);
int setmemopt(int opt_qty, char ***opt);
int releasemem(char ***dir, char ***opt);
int _isdir(char *path);

/* util */
int _strcmp(char *s1, char *s2);
void  _arraycat(char **arr1, char **arr2);

/* bsort */
int bsort(char **array);
void _swap(char **array, int a, int b);
int _arraylen(char **array);

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
struct dirent *r_entry;

#endif /* GOGOMILLAN */
