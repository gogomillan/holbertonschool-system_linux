#include "hls.h"

/**
 * _strcmp - Compare a string to another
 * @s1: The first array
 * @s2: The second array
 *
 * Return: 0, greater than 0 or less than 0
 */
int _strcmp(char *s1, char *s2)
{
int i = 0, r = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		r = s1[i] - s2[i];
		if (r != 0)
			return (r);
		if (s1[i + 1] == '\0' && s2[i + 1] != '\0')
			r = s1[i + 1] - s2[i + 1];
		else if (s1[i + 1] != '\0' && s2[i + 1] == '\0')
			r = s1[i + 1] - s2[i + 1];
		if (r != 0)
			return (r);
		i++;
	}

	return (r);
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
char *time;
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
	time = ctime(&(sb.st_mtime)), *(time + 16) = '\0';

	sprintf(str, "%c%c%c%c%c%c%c%c%c%c %d %s %s %5d %s %s",
		t[(sb.st_mode & S_IFMT) / 010000],
		r[(sb.st_mode & S_IRWXU) / 0100],
		w[(sb.st_mode & S_IRWXU) / 0100],
		x[(sb.st_mode & S_IRWXU) / 0100],
		r[(sb.st_mode & S_IRWXG) / 010],
		w[(sb.st_mode & S_IRWXG) / 010],
		x[(sb.st_mode & S_IRWXG) / 010],
		r[(sb.st_mode & S_IRWXO)],
		w[(sb.st_mode & S_IRWXO)],
		x[(sb.st_mode & S_IRWXO)],
		(int)sb.st_nlink, usr->pw_name, grp->gr_name,
		(int)sb.st_size, (time + 4), path);

	return (str);
}
