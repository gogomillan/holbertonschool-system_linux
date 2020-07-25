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
 * @files: Pointer to the files structure in memory
 * @sizes: Pointer to the sizes structure in memory
 * @t_fls: Total number of files
 *
 * Return: Pointer to the user name
 */
int _gmfiles(char ***files, char ***sizes, ssize_t t_fls)
{
int iter;

	*files = malloc((t_fls + 1) * sizeof(char *));
	if (*files == NULL)
		return (EXIT_FAILURE);

	*sizes = malloc((t_fls + 1) * sizeof(char *));
	if (*sizes == NULL)
	{
		free(*files);
		return (EXIT_FAILURE);
	}
	for (iter = 0; iter < (t_fls + 1); iter++)
	{
		*(*files + iter) = NULL;
		*(*sizes + iter) = NULL;
	}

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

	tmp = dp;
	while (*tmp != NULL)
		free(*tmp++);

	free(dp);
}
