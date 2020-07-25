#include "hls.h"

/**
 * bsort - Bubble sort algorith optimized
 *
 * @array: Array of string to order
 * @sens: Case sensitive [NOCASE | CASE]
 *
 * Return: EXIT_SUCCESS when success process, EXIT_FAILURE other cases
 */
int bsort(char **array, char sens)
{
int newn = 0, iter, n_elem;

	n_elem = _arraylen(array);
	while (n_elem > 1)
	{
		newn = 0;
		for (iter = 1; iter < n_elem; iter++)
			if (_strcmp(array[iter - 1], array[iter], sens) > 0)
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

/**
 * rbs - Reverse bubble sort algorith optimized
 *
 * @array: Array of string to order
 * @sens: Case sensitive [NOCASE | CASE]
 *
 * Return: EXIT_SUCCESS when success process, EXIT_FAILURE other cases
 */
int rbs(char **array, char sens)
{
int newn = 0, iter, n_elem;

	n_elem = _arraylen(array);
	while (n_elem > 1)
	{
		newn = 0;
		for (iter = 1; iter < n_elem; iter++)
			if (_strcmp(array[iter - 1], array[iter], sens) < 0)
			{
				_swap(array, (iter - 1), iter);
				newn = iter;
			}
		n_elem = newn;
	}

	return (EXIT_SUCCESS);
}

/**
 * bsdc - Bubble sort algorith optimized with double conditional
 *
 * @arr1: First array of string to order
 * @ord1: Order for first array of strings [ASC | DES]
 * @arr2: Second array of string to order
 * @ord2: Order for second array of strings [ASC | DES]
 * @sens: Case sensitive [NOCASE | CASE]
 *
 * Return: EXIT_SUCCESS when success process, EXIT_FAILURE other cases
 */
int bsdc(char **arr1, char ord1, char **arr2, char ord2, char sens)
{
int newn = 0, iter, n_elem, diff1, diff2;

	n_elem = _arraylen(arr1);
	while (n_elem > 1)
	{
		newn = 0;
		for (iter = 1; iter < n_elem; iter++)
		{
			diff1 = _strcmp(arr1[iter - 1], arr1[iter], sens);
			diff2 = _strcmp(_trmdt(arr2[iter - 1]), _trmdt(arr2[iter]), sens);
			if (ord1 == ASC && diff1 > 0)
				_swap(arr1, (iter - 1), iter), _swap(arr2, (iter - 1), iter), newn = iter;
			else if ((ord1 == ASC && diff1 == 0) && (ord2 == ASC && diff2 > 0))
				_swap(arr1, (iter - 1), iter), _swap(arr2, (iter - 1), iter), newn = iter;
			else if ((ord1 == ASC && diff1 == 0) && (ord2 == DES && diff2 < 0))
				_swap(arr1, (iter - 1), iter), _swap(arr2, (iter - 1), iter), newn = iter;
			else if (ord1 == DES && diff1 < 0)
				_swap(arr1, (iter - 1), iter), _swap(arr2, (iter - 1), iter), newn = iter;
			else if ((ord1 == DES && diff1 == 0) && (ord2 == ASC && diff2 > 0))
				_swap(arr1, (iter - 1), iter), _swap(arr2, (iter - 1), iter), newn = iter;
			else if ((ord1 == DES && diff1 == 0) && (ord2 == DES && diff2 < 0))
				_swap(arr1, (iter - 1), iter), _swap(arr2, (iter - 1), iter), newn = iter;
		}
		n_elem = newn;
	}

	return (EXIT_SUCCESS);
}
