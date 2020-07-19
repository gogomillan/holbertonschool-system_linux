#include "hls.h"

/**
 * bsort - Bubble sort algorith optimized
 *
 * @array: Array of string to order
 * @n_elem: Number of elements
 *
 * Return: EXIT_SUCCESS when success process, EXIT_FAILURE other cases
 */
int bsort(char **array, int n_elem)
{
int newn = 0, i;

	while (n_elem > 1)
	{
		newn = 0;
		for (i = 1; i < n_elem; i++)
			if (_strcmp(array[i - 1], array[i]) > 0)
			{
				_swap(array, (i - 1), i);
				newn = i;
			}
		n_elem = newn;
	}

	return (EXIT_SUCCESS);
}

/**
 * _swap - interchange two array positions
 *
 * @array: The array
 * @a: The first position
 * @b: The second position
 *
 * Return: Nothin
 */
void _swap(char **array, int a, int b)
{
char *tmp;

	tmp = array[a];
	array[a] = array[b];
	array[b] = tmp;
}
