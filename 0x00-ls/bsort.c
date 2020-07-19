#include "hls.h"

/**
 * bsort - Bubble sort algorith optimized
 *
 * @array: Array of string to order
 *
 * Return: EXIT_SUCCESS when success process, EXIT_FAILURE other cases
 */
int bsort(char **array)
{
int newn = 0, iter, n_elem;

	n_elem = _arraylen(array);
	while (n_elem > 1)
	{
		newn = 0;
		for (iter = 1; iter < n_elem; iter++)
			if (_strcmp(array[iter - 1], array[iter]) > 0)
			{
				_swap(array, (iter - 1), iter);
				newn = iter;
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

/**
 * _arraylen - Gets the len of an array of strings NULL ended
 *
 * @array: Double pointer to the structure
 *
 * Return: Number of elements
 */
int _arraylen(char **array)
{
int qty = 0;

	while (*array++ != NULL)
		qty++;

	return (qty);
}
