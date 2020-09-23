#include "hls.h"

/**
 * _gsize - Return the size of a file
 *
 * @dir: Directory name
 * @path: String with the path to the specific file
 *
 * Return: Pointer to the user name
 */
off_t _gsize(char *dir, char *path)
{
/**
 * stat - struct for file information
 */
struct stat sb;
char str[256];

	sprintf(str, "%s/%s%c", dir, path, '\0');
	if (lstat(str, &sb) == -1)	/* If the path has a problem */
		return (0);

	return (sb.st_size);
}

/**
 * _gmfiles - Return the malloc memory for the file names and size
 *
 * @fls: Pointer to the files structure in memory
 * @szs: Pointer to the sizes structure in memory
 * @tfl: Total number of files
 * @ldrs: List of subdirectories
 * @tdr: Total number of subdirectories
 *
 * Return: Pointer to the user name
 */
int _gmfiles(char ***fls, char ***szs, ssize_t tfl, char ***ldrs, ssize_t tdr)
{
int iter;

	*fls = malloc((tfl + 1) * sizeof(char *));
	if (*fls == NULL)
		return (EXIT_FAILURE);

	*szs = malloc((tfl + 1) * sizeof(char *));
	if (*szs == NULL)
	{	free(*fls);
		return (EXIT_FAILURE);
	}

	*ldrs = malloc((tdr + 1) * sizeof(char *));
	if (*ldrs == NULL)
	{	free(*fls);
		free(*szs);
		return (EXIT_FAILURE);
	}

	for (iter = 0; iter < (tfl + 1); iter++)
	{	*(*fls + iter) = NULL;
		*(*szs + iter) = NULL;
	}
	for (iter = 0; iter < (tdr + 1); iter++)
		*(*ldrs + iter) = NULL;

	return (EXIT_SUCCESS);
}

/**
 * _freedp - Free a double pointer structure
 *
 * @dp: Double pointer
 *
 */
void _freedp(char **dp)
{
char **tmp;

	if (dp == NULL)
		return;

	tmp = dp;
	while (*tmp != NULL)
		free(*tmp++);

	free(dp);
}

/**
 * _trmdt - Trim dots at the very begging. Useful for sorting.
 *
 * @str: String
 *
 * Return: Pointer to the first position without dot
 */
char *_trmdt(char *str)
{
char *pt, flag = FALSE;

	pt = str;

	while (*pt == '.')
	{
		++pt;
		if (*pt != '.' && *pt != '\0')
			flag = TRUE;
	}

	if (flag == TRUE)
		return (pt);
	return (str);
}

/**
 * _gtime - Return the mtime of a file
 *
 * @dir: Directory name
 * @path: String with the path to the specific file
 *
 * Return: Pointer to the user name
 */
time_t _gtime(char *dir, char *path)
{
/**
 * stat - struct for file information
 */
struct stat sb;
char str[256];

	sprintf(str, "%s/%s%c", dir, path, '\0');
	if (lstat(str, &sb) == -1)	/* If the path has a problem */
		return (0);

	return (sb.st_mtime);
}
