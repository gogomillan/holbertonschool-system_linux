#include "hls.h"

/**
 * countagrs - Count the number of arguments to get dirs and opts quantities
 *
 * @argv: The args
 * @dir_qty: Counter for directories
 * @opt_qty: Counter for options
 *
 * Return: EXIT_SUCCESS
 */
int countagrs(char **argv, int *dir_qty, int *opt_qty)
{
int dir = 0;
int opt = 0;
char *arg;

	while (*argv != NULL)  /* Go through the argument list */
	{
		arg = *argv;
		if (*arg == '-')  /* If the arg is an option */
			while (*arg != '\0')
			{
				arg++;
				if (*arg != '\0')
					opt++;
			}
		else             /* Else if it is a directory */
			dir++;
		argv++;
	}
	*dir_qty = dir;
	*opt_qty = opt;

	return (EXIT_SUCCESS);
}

/**
 * setmemdir - Get the memory to create the directory data structure
 *
 * @dir_qty: Qty of files / dirs
 * @dir: Pointer for dirs structure
 * @fil: Pointer for files structure
 * @tmp: Pointer for files/dirs temporary structure
 *
 * Return: EXIT_SUCCESS if process ok, EXIT_FAILURE other cases
 */
int setmemdir(int dir_qty, char ***fil, char ***dir, char ***tmp)
{
int iter = 0;

	*tmp = malloc((dir_qty + 1) * sizeof(char *)); /* Temporary for fils */
	if (*tmp == NULL)
		return (EXIT_FAILURE);
	for (iter = 0; iter < (dir_qty + 1); iter++)
		*(*tmp + iter) = NULL;
	*fil = malloc((dir_qty + 1) * sizeof(char *)); /* Memory for fils */
	if (*fil == NULL)
	{	free(*tmp);
		return (EXIT_FAILURE);
	}
	for (iter = 0; iter < (dir_qty + 1); iter++)
		*(*fil + iter) = NULL;

	if (dir_qty == 0)	/* When there are no dirs */
	{
		*dir = malloc(2 * sizeof(char *));
		if (*dir == NULL)
		{	free(*tmp);
			free(*fil);
			return (EXIT_FAILURE);
		}
		**dir = ".";
		*(*dir + 1) = NULL;
	}
	else				/* Else if there are directories */
	{
		*dir = malloc((dir_qty + 1) * sizeof(char *));
		if (*dir == NULL)
		{	free(*tmp), free(*fil);
			return (EXIT_FAILURE);
		}
		for (iter = 0; iter < (dir_qty + 1); iter++)
			*(*dir + iter) = NULL;
	}
	return (EXIT_SUCCESS);
}

/**
 * setmemopt - Get the memory to create the options data structure
 *
 * @opt_qty: Qty of options
 * @opt: Pointer for options structure
 *
 * Return: EXIT_SUCCESS if process ok, EXIT_FAILURE other cases
 */
int setmemopt(int opt_qty, char ***opt)
{
int iter;

	if (opt_qty == 0)	/* When there are no options */
	{
		*opt = malloc(sizeof(char *));
		if (*opt == NULL)
			return (EXIT_FAILURE);
		**opt = NULL;
	}
	else				/* Else if there are options */
	{
		*opt = malloc((opt_qty + 1) * sizeof(char *));
		if (*opt == NULL)
			return (EXIT_FAILURE);
		for (iter = 0; iter < (opt_qty + 1); iter++)
			*(*opt + iter) = NULL;
	}
	return (EXIT_SUCCESS);
}

/**
 * releasemem - Release memory from dirs and opts to heap
 *
 * @fil: Pointer to fils memory
 * @dir: Pointer to dirs memory
 * @opt: Pointer to opts memory
 *
 * Return: EXIT_SUCCESS if process ok, EXIT_FAILURE other cases
 */
int releasemem(char ***fil, char ***dir, char ***opt)
{
char **opts;

	free(*fil);		/* Realease memory from files */
	*fil = NULL;

	free(*dir);		/* Realease memory from dirs */
	*dir = NULL;

	opts = *opt;	/* Release memory from options array */
	while (*opts != NULL)
		free(*opts++);		/* For every single option */
	free(*opt);
	*opt = NULL;

	return (EXIT_SUCCESS);
}

/**
 * _isdir - Check a path to verify if directory or other
 *
 * @dir: The base dir
 * @path: The path as a string
 *
 * Return: Type of file or -1 other cases
 */
int _isdir(char *dir, char *path)
{
char str[512];
struct stat sb;

	if (dir != NULL)
	{
		sprintf(str, "%s/%s", dir, path);
		if (lstat(str, &sb) == -1)
			return (-1);
	}
	else
	{
		if (lstat(path, &sb) == -1)
			return (-1);
	}

	return (sb.st_mode & S_IFMT);
}
