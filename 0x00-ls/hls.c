#include "hls.h"

/**
 * main - Main function for my own ls project
 *
 * @argc: Number of arguments
 * @argv: The arguments from OS invocation
 *
 * Return: EXIT_SUCCESS when alright, EXIT_FAILURE in other case
 */
int main(int argc, char **argv)
{
char **fil;		/* list of file(s) */
char **dir;		/* list of directorie(s) */
char **opt;		/* list of option(s) */

	(void)argc;

	if (getargs(argv, &fil, &dir, &opt) != EXIT_SUCCESS)
		return (EXIT_FAILURE);

	if (_readdir(fil, dir, opt) != EXIT_SUCCESS)
	{
		releasemem(&fil, &dir, &opt);
		return (2);
	}

	releasemem(&fil, &dir, &opt);
	return (EXIT_SUCCESS);
}
