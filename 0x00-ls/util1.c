#include "hls.h"

/**
 * intlen - Return the lenght in digits for an integer
 *
 * @vr: The value
 *
 * Return: Number of digits
 */
int intlen(int vr)
{
int cont = 1, digit = 1;

	while ((vr / (digit * 10)) > 0)
		digit *= 10, cont++;
	return (cont);
}
