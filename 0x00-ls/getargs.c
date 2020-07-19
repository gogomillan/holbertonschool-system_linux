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
int dir_qty = 0, opt_qty = 0;			/* Number of dirs /files & options */
char *arg, **dir, **opt, **tdir, **tmp;	/* For each argument, dirs and opts */

	if (countagrs(++argv, &dir_qty, &opt_qty) != EXIT_SUCCESS) /* Counting args */
		return (EXIT_FAILURE);
	if (setmemdir(dir_qty, dirs, &tdir) != EXIT_SUCCESS) /* Getting mem for dir */
		return (EXIT_FAILURE);
	if (setmemopt(opt_qty, opts) != EXIT_SUCCESS) /* Getting mem for options */
	{	releasemem(dirs, opts);
		return (EXIT_FAILURE);
	}

	dir = *dirs, opt = *opts, tmp = tdir;	/* Looking for dirs & opts in args */
	while (*argv != NULL)
	{	arg = *argv;
		if (*arg != '-')	/* If the arg is a file / dir */
			if (_isdir(arg) == EXIT_SUCCESS)
			{	*tmp = arg, tmp++, *tmp = NULL;
			}
			else
			{	*dir = arg, dir++, *dir = NULL;
			}
		else				/* Else if it is an option or set of options */
			while (*arg != '\0')
			{	arg++;
				if (*arg != '\0')
				{	*opt = malloc(2 * sizeof(char));
					if (*opt == NULL)
						return (EXIT_FAILURE);
					*opt[0] = *arg, *opt[1] = '\0', opt++, *opt = NULL;
				}
			}
		argv++;
	}
	bsort(*dirs);
	bsort(tdir);
	_arraycat(*dirs, tdir);
	free(tdir);

	return (EXIT_SUCCESS);
}
