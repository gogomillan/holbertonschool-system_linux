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
 * @dir: Pointer for files/dirs structure
 * @tmp: Pointer for files/dirs temporary structure
 *
 * Return: EXIT_SUCCESS if process ok, EXIT_FAILURE other cases
 */
int setmemdir(int dir_qty, char ***dir, char ***tmp)
{
int iter = 0;

	*tmp = malloc((dir_qty + 1) * sizeof(char *)); /* Temporary for dirs */
	if (*tmp == NULL)
		return (EXIT_FAILURE);
	**tmp = NULL;

	if (dir_qty == 0)	/* When there are no dirs */
	{
		*dir = malloc(2 * sizeof(char *));
		if (*dir == NULL)
		{
			free(*tmp);
			return (EXIT_FAILURE);
		}
		**dir = malloc(2 * sizeof(char));
		if (**dir == NULL)
		{
			free(*tmp);
			free(*dir);
			return (EXIT_FAILURE);
		}
		sprintf(**dir, ".");
		*(*dir + 1) = NULL;
	}
	else				/* Else if there are directories */
	{
		*dir = malloc((dir_qty + 1) * sizeof(char *));
		if (*dir == NULL)
		{
			free(*tmp);
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
	}
	return (EXIT_SUCCESS);
}

/**
 * releasemem - Release memory from dirs and opts to heap
 *
 * @dir: Pointer to dirs memory
 * @opt: Pointer to opts memory
 *
 * Return: EXIT_SUCCESS if process ok, EXIT_FAILURE other cases
 */
int releasemem(char ***dir, char ***opt)
{
char **dirs, **opts;

	dirs = *dir;	/* Realease memory from dirs array */
	if (**dirs == '.' && *(dirs + 1) == NULL)
		while (*dirs != NULL)
			free(*dirs++);	/* Only if it didn't have dirs args */
	free(*dir);
	*dir = NULL;

	opts = *opt;	/* Release memry from options array */
	while (*opts != NULL)
		free(*opts++);		/* For every single option */
	free(*opt);
	*opt = NULL;

	return (EXIT_SUCCESS);
}

/**
 * _isdir - Check a path to verify if directory
 *
 * @path: The path as a string
 *
 * Return: EXIT_SUCCESS if is a dir or EXIT_FAILURE other cases
 */
int _isdir(char *path)
{
struct stat sb;

	if (stat(path, &sb) == -1)
		return (EXIT_FAILURE);

	if ((sb.st_mode & S_IFMT) == S_IFDIR)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
