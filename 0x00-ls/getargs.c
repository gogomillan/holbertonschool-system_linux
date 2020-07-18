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

	/* Counting args get from OS line command */
	if (countagrs(++argv, &dir_qty, &opt_qty) != EXIT_SUCCESS)
		return (EXIT_FAILURE);

	/* Getting memory to store the files / dirs in argv */
	if (setmemdir(dir_qty, dirs) != EXIT_SUCCESS)
	{	releasemem(dirs, opts);
		return (EXIT_FAILURE);
	}

	/* Getting memory to store the options in argv */
	if (setmemopt(opt_qty, opts) != EXIT_SUCCESS)
	{	releasemem(dirs, opts);
		return (EXIT_FAILURE);
	}

	dir = *dirs, opt = *opts;
	while (*argv != NULL)
	{	arg = *argv;
		if (*arg != '-')
		{	*dir = arg;
			dir++, *dir = NULL;
		}
		else
			while (*arg != '\0')
			{	arg++;
				if (*arg != '\0')
					*opt = malloc(2 * sizeof(char));
					if (*opt == NULL)
						return (EXIT_FAILURE);
					*opt[0] = *arg, *opt[1] = '\0', opt++, *opt = NULL;
			}
		argv++;
	}
	return (EXIT_SUCCESS);
}

/**
 * countagrs - Count the number of arguments
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

	while (*argv != NULL)
	{
		arg = *argv;
		if (*arg == '-')
			while (*arg != '\0')
			{
				arg++;
				if (*arg != '\0')
					opt++;
			}
		else
			dir++;
		argv++;
	}
	*dir_qty = dir;
	*opt_qty = opt;

	return (EXIT_SUCCESS);
}

/**
 * setmemdir - Create the directory data structure
 *
 * @dir_qty: Qty of files / dirs
 * @dir: Pointer for files/dirs structure
 *
 * Return: EXIT_SUCCESS if process ok, EXIT_FAILURE other cases
 */
int setmemdir(int dir_qty, char ***dir)
{

	if (dir_qty == 0)
	{
		*dir = malloc(2 * sizeof(char *));
		if (*dir == NULL)
			return (EXIT_FAILURE);
		**dir = malloc(2 * sizeof(char));
		sprintf(**dir, ".");
		*(*dir + 1) = NULL;
	}
	else
	{
		*dir = malloc((dir_qty + 1) * sizeof(char *));
		if (*dir == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * setmemopt - Create the options data structure
 *
 * @opt_qty: Qty of options
 * @opt: Pointer for options structure
 *
 * Return: EXIT_SUCCESS if process ok, EXIT_FAILURE other cases
 */
int setmemopt(int opt_qty, char ***opt)
{
	if (opt_qty == 0)
	{
		*opt = malloc(sizeof(char *));
		if (*opt == NULL)
			return (EXIT_FAILURE);
		**opt = NULL;
	}
	else
	{
		*opt = malloc((opt_qty + 1) * sizeof(char *));
		if (*opt == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * releasemem - Release memory from heap
 *
 * @dir: Pointer to dirs memory
 * @opt: Pointer to opts memory
 *
 * Return: EXIT_SUCCESS if process ok, EXIT_FAILURE other cases
 */
int releasemem(char ***dir, char ***opt)
{
char **dirs, **opts;

	dirs = *dir;
	while (*dirs != NULL)
		free(*dirs++);
	free(dirs);
	*dir = NULL;

	opts = *opt;
	while (*opts != NULL)
		free(*opts++);
	free(opts);
	opt = NULL;

	return (EXIT_SUCCESS);
}
