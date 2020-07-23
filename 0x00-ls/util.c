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
struct passwd *usr;
struct group *grp;
int iter, w_ln;

	if (*dir == '\0')			/* Path without dir */
		sprintf(str, "%s%c", path, '\0');
	else						/* Path with dir */
		sprintf(str, "%s/%s%c", dir, path, '\0');
	if (lstat(str, &sb) == -1)	/* If the path has a problem */
		return (str);
	usr = getpwuid(sb.st_uid), grp = getgrgid(sb.st_gid);	/* User &  Group */
	if (usr != NULL)
		sprintf(susr, "%s%c", usr->pw_name, '\0');	/* Buffer for user name  */
	else
		sprintf(susr, "%d%c", (int)sb.st_uid, '\0');	/* Buff for usr code */
	if (grp != NULL)
		sprintf(sgrp, "%s%c", grp->gr_name, '\0');	/* Buffer for group name */
	else
		sprintf(sgrp, "%d%c", (int)sb.st_gid, '\0');	/* Buff for grp code */
	time = ctime(&(sb.st_mtime)), *(time + 16) = '\0';	/* Buff for DateTime */
	if ((sb.st_mode & S_IFMT) == S_IFLNK)
		getlname(str, lpath, sb.st_size);	/* Get the  symlink pointed  dir */
	w_ln = _dirstat(path, W_LINK);
	for (iter = 0; iter < 512; iter++)		/* Initialize  the  buffer  line */
		str[iter] = '\0';
	sprintf(str, "%c%c%c%c%c%c%c%c%c%c %*d %s %s %5d %s %s%s",/* The line */
		t[(sb.st_mode & S_IFMT) / 010000], r[(sb.st_mode & S_IRWXU) / 0100],
		w[(sb.st_mode & S_IRWXU) / 0100], x[(sb.st_mode & S_IRWXU) / 0100],
		r[(sb.st_mode & S_IRWXG) / 010], w[(sb.st_mode & S_IRWXG) / 010],
		x[(sb.st_mode & S_IRWXG) / 010], r[(sb.st_mode & S_IRWXO)],
		w[(sb.st_mode & S_IRWXO)], x[(sb.st_mode & S_IRWXO)], w_ln, (int)sb.st_nlink,
		susr, sgrp, (int)sb.st_size, (time + 4), path, lpath);
	return (str);
}


/**
 * _dirstat - Define stats for files from a dirs
 *
 * @dirs: The path to the directory
 * @stat: The statistic needed
 *
 * Return: The statistic value needed
 */
int _dirstat(char *dirs, char stat)
{
static int w_link, w_usrs, w_grps, w_size;	/* stats vars */
char susr[128], sgrp[128], str[512], flag_a, flag_A;			/* Buffers */
DIR *dir;									/* Structure to the directory  */
/**
 * stat - struct for file information
 */
struct stat sb;
struct passwd *usr;
struct group *grp;

	(void)susr, (void)sgrp, (void)str, (void)usr, (void)grp;
	if (stat == W_INIT)
	{	dir = opendir(dirs);							/* Open the dir			 */
		flag_a = _format("a", GET), flag_A = _format("A", GET);
		while ((r_entry = readdir(dir)) != NULL)		/* For each dir entrance */
			if ((flag_A == EXIT_SUCCESS &&	/* If opt A and not dir "." or ".." */
				_strcmp(r_entry->d_name, ".", NOCASE) != 0 &&
				_strcmp(r_entry->d_name, "..", NOCASE) != 0) ||
				flag_a == EXIT_SUCCESS ||	/* Or option "a" is set             */
				r_entry->d_name[0] != '.')	/* Or dir name starting without "." */
			{
				sprintf(str, "%s/%s%c", dirs, r_entry->d_name, '\0');
				if (lstat(str, &sb) == -1)	/* If the path has a problem */
					continue;
				if ((int)sb.st_nlink > w_link)
					w_link = (int)sb.st_nlink;
				if ((int)sb.st_size > w_size)
					w_size = (int)sb.st_size;
			}
		w_link = intlen(w_link);
	}
	if (stat == W_LINK)
		return (w_link);
	if (stat == W_USRS)
		return (w_usrs);
	if (stat == W_GRPS)
		return (w_grps);
	if (stat == W_SIZE)
		return (w_size);
	return (EXIT_SUCCESS);
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
