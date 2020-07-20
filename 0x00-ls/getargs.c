#include "hls.h"

/**
 * getargs - get the arguments / options from argv
 *
 * @argv: The list of arguments / options
 * @fils: List of files to list
 * @dirs: List of directories to list
 * @opts: List of option
 *
 * Return: EXIT_SUCCESS when successfuly, EXIT_FAILURE other cases
 */
int getargs(char **argv, char ***fils, char ***dirs, char ***opts)
{
int dir_qty = 0, opt_qty = 0, f_type;	/* Number of dirs /files & options */
char *arg, **dir, **opt, **fil, **tdir, **tmp;	/* For each argument */

	if (countagrs(++argv, &dir_qty, &opt_qty) != EXIT_SUCCESS) /* Counting args */
		return (EXIT_FAILURE);
	if (setmemdir(dir_qty, fils, dirs, &tdir) != EXIT_SUCCESS) /* Mem for dir */
		return (EXIT_FAILURE);
	if (setmemopt(opt_qty, opts) != EXIT_SUCCESS) /* Getting mem for options */
	{	releasemem(fils, dirs, opts);
		return (EXIT_FAILURE);
	}
	dir = *dirs, opt = *opts, fil = *fils, tmp = tdir;	/* Reviewing args */
	while (*argv != NULL)
	{	arg = *argv;
		if (*arg != '-')	/* If the arg is a file / dir */
		{	f_type = _isdir(arg);
			if (f_type == S_IFDIR)		/* Is a dir */
			{	*dir = arg, dir++, *dir = NULL;
			}
			else if (f_type == S_IFREG)	/* Is a reg file */
			{	*tmp = arg, tmp++, *tmp = NULL;
			}
			else						/* Is other case */
			{	*fil = arg, fil++, *fil = NULL;
			}
		}
		else				/* Else if it is an option or set of options */
			while (*arg != '\0')
			{	arg++;
				if (*arg != '\0')
				{	*opt = malloc(2 * sizeof(char));
					if (*opt == NULL)
						return (EXIT_FAILURE);
					**opt = *arg, *(*opt + 1) = '\0', opt++, *opt = NULL;
				}
			}
		argv++;
	}
	bsort(*dirs), bsort(*fils), bsort(tdir), _arraycat(*fils, tdir), free(tdir);
	return (EXIT_SUCCESS);
}
