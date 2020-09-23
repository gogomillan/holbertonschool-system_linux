#ifndef GOGOMILLAN
#define GOGOMILLAN OK

#define TRUE  1
#define FALSE 0

#define NOCASE 0
#define CASE   1

#define ASC 10
#define DES 20

#define PUT 0
#define GET 1

#define W_INIT 0
#define W_LN 1
#define W_UR 2
#define W_GR 3
#define W_SZ 4
#define N_FL 5
#define N_DI 6

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
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
int _isdir(char *dir, char *path);

/* util */
int _strcmp(char *s1, char *s2, char sens);
void  _arraycat(char **arr1, char **arr2);
char *frmt_l(char *dir, char *path);
char *getlname(char *path, char *str, off_t st_size);
int _dstat(char *dirs, char stat);

/* util1 */
int intlen(int vr);
int _strlen(char *str);
char *_guid(uid_t st_uid, char *susr);
char *_ggid(gid_t st_gid, char *sgrp);
char ***dtom(char *dirs, size_t t_fls, size_t t_drs);

/* util2 */
off_t _gsize(char *dir, char *path);
int _gmfiles(char ***fls, char ***szs, ssize_t tfs, char ***ldrs, ssize_t tds);
void _freedp(char **dp);
char *_trmdt(char *str);
time_t _gtime(char *dir, char *path);

/* Util3 */
void _sfd(char **sz, char **fl, char cs);

/* bsort */
int bsort(char **array, char sens);
void _swap(char **array, int a, int b);
int _arraylen(char **array);
int rbs(char **array, char sens);
int bsdc(char **arr1, char ord1, char **arr2, char ord2, char sens);

/* readdir */
void set_format(char *opt);
int _prndir(char *dirs, char dirprnctrl);
int _prnfiles(char **files, char *dirprnctrl);
char *geterrmsg(char *path);
int _format(char *opt, char oper);

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
