#include "hls.h"

/**
 * _strcmp - Compare a string to another
 * @s1: The first array
 * @s2: The second array
 * @sens: Case sensitive [NOCASE | CASE]
 *
 * Return: 0, greater than 0 or less than 0
 */
int _strcmp(char *s1, char *s2, char sens)
{
int iter = 0, ret = 0;
char a, b;

	while (s1[iter] != '\0' && s2[iter] != '\0')	/* Go through the both string */
	{
		a = s1[iter], b = s2[iter];			/* Evaluates the current position */
		if (sens == NOCASE)		/* In no case sensitive */
		{
			if (a >= 65 && a <= 90)
				a += 32;
			if (b >= 65 && b <= 90)
				b += 32;
		}
		ret = a - b;
		if (ret != 0)	/* If different returns the difference */
			return (ret);
		a = s1[iter + 1], b = s2[iter + 1];	/* Evaluates one pos in advance */
		if ((a == '\0' && b != '\0') || (a != '\0' && b == '\0'))
		{
			if (sens == NOCASE)	/* For no case sensitive */
			{
				if (a >= 65 && a <= 90)
					a += 32;
				if (b >= 65 && b <= 90)
					b += 32;
			}
			ret = a - b;
		}
		if (ret != 0)	/* If different returns the difference */
			return (ret);
		iter++;				/* Next iteration */
	}															/*** End while ***/

	return (ret);		/* If no differences */
}

/**
 * _arraycat - Appends two array of strings. It adds arr2 at the end of arr1
 *
 * @arr1: Double pointer to the array 1
 * @arr2: Double pointer to the array 2
 *
 * Return: EXIT_SUCCESS if success, EXIT_FAILURE in other cases
 */
void _arraycat(char **arr1, char **arr2)
{
	while (*arr1 != NULL)
		arr1++;
	while (*arr2 != NULL)
	{
		*arr1 = *arr2;
		arr1++, arr2++;
	}
	arr1 = NULL;
}

/**
 * frmt_l - Format the file representation for ls -l
 *
 * @dir: The path to the dir
 * @path: The path to the file
 *
 * Return: A char pointer to the structure
 */
char *frmt_l(char *dir, char *path)
{
static char str[512]; /* Result */
char *t = "0pc3d5b7-1l3s", *r = "----rrrr", *w = "--ww--ww", *x = "-x-x-x-x";
char *time, susr[128], sgrp[128], lpath[512] = { '\0' };
/**
 * stat - struct for file information
 */
struct stat sb;
int iter, w_ln, w_sz, w_ur, w_gr;

	if (*dir == '\0')			/* Path without dir */
		sprintf(str, "%s%c", path, '\0');
	else						/* Path with dir */
		sprintf(str, "%s/%s%c", dir, path, '\0');
	if (lstat(str, &sb) == -1)	/* If the path has a problem */
		return (str);

	_guid(sb.st_uid, susr); /* User  */
	_ggid(sb.st_gid, sgrp); /* Group */
	time = ctime(&(sb.st_mtime)), *(time + 16) = '\0';	/* Buff for DateTime */
	if ((sb.st_mode & S_IFMT) == S_IFLNK)
		getlname(str, lpath, sb.st_size);	/* Get the  symlink pointed  dir */

	w_ln = _dstat(path, W_LN), w_sz = _dstat(path, W_SZ);
	w_ur = _dstat(path, W_UR), w_gr = _dstat(path, W_GR);
	for (iter = 0; iter < 512; iter++)		/* Initialize  the  buffer  line */
		str[iter] = '\0';

	sprintf(str, "%c%c%c%c%c%c%c%c%c%c %*d %*s %*s %*d %s %s%s",/* The line */
		t[(sb.st_mode & S_IFMT) / 010000], r[(sb.st_mode & S_IRWXU) / 0100],
		w[(sb.st_mode & S_IRWXU) / 0100], x[(sb.st_mode & S_IRWXU) / 0100],
		r[(sb.st_mode & S_IRWXG) / 010], w[(sb.st_mode & S_IRWXG) / 010],
		x[(sb.st_mode & S_IRWXG) / 010], r[(sb.st_mode & S_IRWXO)],
		w[(sb.st_mode & S_IRWXO)], x[(sb.st_mode & S_IRWXO)], w_ln, (int)sb.st_nlink,
		-w_ur, susr, -w_gr, sgrp, w_sz, (int)sb.st_size, (time + 4), path, lpath);
	return (str);
}

/**
 * _dstat - Define stats for files from a dirs
 *
 * @dirs: The path to the directory
 * @stat: The statistic needed
 *
 * Return: The statistic value needed
 */
int _dstat(char *dirs, char stat)
{
static int st[8], w_tmp;						/* stats vars */
char str[512], str_ug[256], fg_a, fg_A, fg_R;		/* Buffers    */
DIR *dir;						/* Structure to the directory  */
/**
 * stat - struct for file information
 */
struct stat sb;

	if (stat == W_INIT)
	{
		dir = opendir(dirs), st[N_FL] = 0, st[N_DI] = 0;				/* Open the dir			 */
		fg_a = _format("a", GET), fg_A = _format("A", GET), fg_R = _format("R", GET);
		while ((r_entry = readdir(dir)) != NULL)		/* For each dir entrance */
			if ((fg_A == EXIT_SUCCESS && _strcmp(r_entry->d_name, ".", NOCASE) != 0 &&
				_strcmp(r_entry->d_name, "..", NOCASE) != 0) ||	/* Opt A & no dir . or ..*/
				fg_a == EXIT_SUCCESS || r_entry->d_name[0] != '.')	/* Opt a Or dirname */
			{
				sprintf(str, "%s/%s%c", dirs, r_entry->d_name, '\0');
				if (lstat(str, &sb) == -1)	/* If the path has a problem */
					continue;
				st[W_LN] = ((int)sb.st_nlink > st[W_LN]) ? (int)sb.st_nlink : st[W_LN];
				st[W_SZ] = ((int)sb.st_size > st[W_SZ]) ? (int)sb.st_size : st[W_SZ];
				w_tmp = _strlen(_guid(sb.st_uid, str_ug));
				st[W_UR] = (w_tmp > st[W_UR]) ?  w_tmp : st[W_UR];
				w_tmp = _strlen(_ggid(sb.st_gid, str_ug));
				st[W_GR] = (w_tmp > st[W_GR]) ?  w_tmp : st[W_GR], st[N_FL]++;
				if (fg_R == EXIT_SUCCESS)
					st[N_DI] = ((sb.st_mode & S_IFMT) == S_IFDIR) ? st[N_DI] + 1 : st[N_DI];
			}
		st[W_LN] = intlen(st[W_LN]), st[W_SZ] = intlen(st[W_SZ]), closedir(dir);
	}
	return (st[(int)stat]);
}

/**
 * getlname - Get the paht pointed by the symbolic link
 *
 * @path: Link path that points
 * @str: Buffer to store the result
 * @st_size: Lenght of the link name
 *
 * Return: The pointer to the string that represent the full path
 */
char *getlname(char *path, char *str, off_t st_size)
{
char *linkname = NULL;
ssize_t r;

	linkname = malloc(st_size + 1);
	if (linkname != NULL)
	{
		r = readlink(path, linkname, st_size + 1);
		r = (r != -1) ? r : 0;
		linkname[r] = '\0';
	}
	sprintf(str, " -> %s%c", linkname, '\0');
	if (linkname != NULL)
		free(linkname);

	return (str);
}
