#include "signals.h"

/**
* main - prints a description of a given signal
* @argc: number of arguments
* @argv: arguments
* Return: 0 on success, 1 otherwise
*/
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	printf("%s: %s\n", argv[1], strsignal(atoi(argv[1])));

	return (EXIT_SUCCESS);
}
