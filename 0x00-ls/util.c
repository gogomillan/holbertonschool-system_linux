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

	while (s1[iter] != '\0' && s2[iter] != '\0')
	{
		a = s1[iter], b = s2[iter];
		if (sens == NOCASE)
		{
			if (a >= 65 && a <= 90)
				a += 32;
			if (b >= 65 && b <= 90)
				b += 32;
		}
		ret = a - b;
		if (ret != 0)
		a = s1[iter + 1], b = s2[iter + 1];
		return (ret);
		if ((a == '\0' && b != '\0') ||
			(a != '\0' && b == '\0'))
		{
			if (sens == NOCASE)
			{
				if (a >= 65 && a <= 90)
					a += 32;
				if (b >= 65 && b <= 90)
					b += 32;
			}
			ret = a - b;
		}
		if (ret != 0)
			return (ret);
		iter++;
	}

	return (ret);
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
static char str[512];	/* Result */
char *t = "0pc3d5b7-1l3s", *r = "----rrrr", *w = "--ww--ww", *x = "-x-x-x-x";
char *time, susr[128], sgrp[128];
/**
 * stat - struct for file information
 */
struct stat sb;
struct passwd *usr;
struct group *grp;
int iter;

	if (*dir == '\0')
		sprintf(str, "%s%c", path, '\0');
	else
		sprintf(str, "%s/%s%c", dir, path, '\0');
	if (lstat(str, &sb) == -1)	/* If the path has a problem */
		return (str);
	for (iter = 0; iter < 512; iter++)
		str[iter] = '\0';
	usr = getpwuid(sb.st_uid), grp = getgrgid(sb.st_gid);
	if (usr != NULL)
		sprintf(susr, "%s%c", usr->pw_name, '\0');
	else
		sprintf(susr, "%d%c", (int)sb.st_uid, '\0');
	if (grp != NULL)
		sprintf(sgrp, "%s%c", grp->gr_name, '\0');
	else
		sprintf(sgrp, "%d%c", (int)sb.st_gid, '\0');
	time = ctime(&(sb.st_mtime)), *(time + 16) = '\0';

	sprintf(str, "%c%c%c%c%c%c%c%c%c%c %d %s %s %5d %s %s",
		t[(sb.st_mode & S_IFMT) / 010000], r[(sb.st_mode & S_IRWXU) / 0100],
		w[(sb.st_mode & S_IRWXU) / 0100], x[(sb.st_mode & S_IRWXU) / 0100],
		r[(sb.st_mode & S_IRWXG) / 010], w[(sb.st_mode & S_IRWXG) / 010],
		x[(sb.st_mode & S_IRWXG) / 010], r[(sb.st_mode & S_IRWXO)],
		w[(sb.st_mode & S_IRWXO)], x[(sb.st_mode & S_IRWXO)], (int)sb.st_nlink, susr,
		sgrp, (int)sb.st_size, (time + 4), path);

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
char susr[128], sgrp[128], str[512];		/* Buffers */
DIR *dir;									/* Structure to the directory */
/**
 * stat - struct for file information
 */
struct stat sb;
struct passwd *usr;
struct group *grp;

	(void)susr, (void)sgrp, (void)str;
	(void)usr, (void)grp;
	dir = opendir(dirs);							/* Open the dir			 */
	while ((r_entry = readdir(dir)) != NULL)		/* For each dir entrance */
	{
		sprintf(str, "%s/%s%c", dirs, r_entry->d_name, '\0');
		if (lstat(str, &sb) == -1)	/* If the path has a problem */
			continue;
		if ((int)sb.st_nlink > w_link)
			w_link = (int)sb.st_nlink;
		if ((int)sb.st_size > w_size)
			w_size = sb.st_size;
	}

	if (stat == W_LINK)
		return (w_link);
	if (stat == W_USRS)
		return (w_usrs);
	if (stat == W_GRPS)
		return (w_grps);
	return (w_size);
}
