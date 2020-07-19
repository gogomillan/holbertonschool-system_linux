#include "hls.h"

/**
 * _strcmp - Compare a string to another
 * @s1: The first array
 * @s2: The second array
 *
 * Return: 0, greater than 0 or less than 0
 */
int _strcmp(char *s1, char *s2)
{
int i = 0, r = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		r = s1[i] - s2[i];
		if (r != 0)
			return (r);
		if (s1[i + 1] == '\0' && s2[i + 1] != '\0')
			r = s1[i + 1] - s2[i + 1];
		else if (s1[i + 1] != '\0' && s2[i + 1] == '\0')
			r = s1[i + 1] - s2[i + 1];
		if (r != 0)
			return (r);
		i++;
	}

	return (r);
}

/**
 * _arraycat - Appends two array of strings. It adds arr2 at the end of arr1
 *
 * @arr1: Double pointer to the array 1
 * @arr2: Double pointer to the array 2
 *
 * Return: EXIT_SUCCESS if success, EXIT_FAILURE in other cases
 */
void _arraycat(char **arr1, char **arr2)
{
	while (*arr1 != NULL)
		arr1++;
	while (*arr2 != NULL)
	{
		*arr1 = *arr2;
		arr1++, arr2++;
	}
	arr1 = NULL;
}
