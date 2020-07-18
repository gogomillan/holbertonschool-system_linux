#include "hls.h"

/**
 * getargs - get the arguments / options from argv
 *
 * @argv: The list of arguments / options
 * @dirs: List of directories / files to list
 * @opts: List of option
 *
 * Return: EXIT_SUCCESS when successfuly, EXIT_FAILURE other cases
 */
int getargs(char **argv, char ***dirs, char ***opts)
{
int dir_qty = 0, opt_qty = 0;	/* Number of dirs /files & options */
char *arg, **dir, **opt;		/* For each argument, dirs and opts */

	if (countagrs(++argv, &dir_qty, &opt_qty) != EXIT_SUCCESS) /* Counting args */
		return (EXIT_FAILURE);

	if (setmemdir(dir_qty, dirs) != EXIT_SUCCESS) /* Getting mem for dirs */
	{	releasemem(dirs, opts);
		return (EXIT_FAILURE);
	}

	if (setmemopt(opt_qty, opts) != EXIT_SUCCESS) /* Getting mem for options */
	{	releasemem(dirs, opts);
		return (EXIT_FAILURE);
	}

	dir = *dirs, opt = *opts; /* Looking for dirs and opts in the args */
	while (*argv != NULL)
	{	arg = *argv;
		if (*arg != '-')  /* If the arg is a file / dir */
		{	*dir = arg;
			dir++, *dir = NULL;
		}
		else             /* Else if it is an option or set of options */
			while (*arg != '\0')
			{	arg++;
				if (*arg != '\0')
				{
					*opt = malloc(2 * sizeof(char));
					if (*opt == NULL)
						return (EXIT_FAILURE);
					*opt[0] = *arg, *opt[1] = '\0', opt++, *opt = NULL;
				}
			}
		argv++;
	}
	return (EXIT_SUCCESS);
}

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
 *
 * Return: EXIT_SUCCESS if process ok, EXIT_FAILURE other cases
 */
int setmemdir(int dir_qty, char ***dir)
{

	if (dir_qty == 0)	/* When there are no dirs */
	{
		*dir = malloc(2 * sizeof(char *));
		if (*dir == NULL)
			return (EXIT_FAILURE);
		**dir = malloc(2 * sizeof(char));
		sprintf(**dir, ".");
		*(*dir + 1) = NULL;
	}
	else				/* Else if there are directories */
	{
		*dir = malloc((dir_qty + 1) * sizeof(char *));
		if (*dir == NULL)
			return (EXIT_FAILURE);
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
