#ifndef GOGOMILLAN
#define GOGOMILLAN OK

#define TRUE  1
#define FALSE 0

#define NOCASE 0
#define CASE   1

#define PUT 0
#define GET 1

#define W_LINK 1
#define W_USRS 2
#define W_GRPS 3
#define W_SIZE 4

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
/*#include <unistd.h>*/
#include <dirent.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>

/* main */
int _readdir(char **fils, char **dirs, char **opts);
int getargs(char **argv, char ***fil, char ***dir, char ***opt);

/* libgetargs */
int countagrs(char **argv, int *dir_qty, int *opt_qty);
int setmemdir(int dir_qty, char ***fil, char ***dir, char ***tmp);
int setmemopt(int opt_qty, char ***opt);
int releasemem(char ***fil, char ***dir, char ***opt);
int _isdir(char *path);

/* util */
int _strcmp(char *s1, char *s2, char sens);
void  _arraycat(char **arr1, char **arr2);
char *frmt_l(char *dir, char *path);

/* bsort */
int bsort(char **array, char sens);
void _swap(char **array, int a, int b);
int _arraylen(char **array);

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
