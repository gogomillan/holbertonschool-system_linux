#include "hls.h"

/**
 * main - Main function for my own ls project
 *
 * Return: EXIT_SUCCESS when alright, EXIT_FAILURE in other case
 */
int main(void)
{
	if (_readdir(".") != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
