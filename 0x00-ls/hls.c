#include "hls.h"

int imprime(char **buff);

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
char **dir;		/* list of file(s) / directorie(s) */
char **opt;		/* list of option(s) */

	(void)argc;

	if (getargs(argv, &dir, &opt) != EXIT_SUCCESS)
		return (EXIT_FAILURE);

	if (_readdir(dir, opt) != EXIT_SUCCESS)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

/**
 * imprime - prints an array of strings
 * @buff: The double pointer to the array or memory space
 * Return: Always 0
 */
int imprime(char **buff)
{
	while (*buff != NULL)
		printf("- %s", *buff++);
	printf("\n");

	return (0);
}
