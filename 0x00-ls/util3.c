#include "hls.h"

/**
 * _sfd - Sort the files and directories content in a dir
 *
 * @sz: Array of Sizes
 * @fl: Array of Files
 * @cs: Case Sensitive [NOCASE | CASE]
 *
 * Return: nothing
 */
void _sfd(char **sz, char **fl, char cs)
{
char flag_r, flag_S, fg_t;

	flag_r = _format("r", GET);	/* GEt flag r */
	flag_S = _format("S", GET);	/* Get flag S */
	fg_t = _format("t", GET);	/* Get flag t */

	if (flag_r != EXIT_SUCCESS && flag_S == EXIT_SUCCESS)
		bsdc(sz, DES, fl, ASC, cs);
	else if (flag_r == EXIT_SUCCESS && flag_S == EXIT_SUCCESS)
		bsdc(sz, ASC, fl, DES, cs);
	else if (flag_r != EXIT_SUCCESS && fg_t == EXIT_SUCCESS)
		bsdc(sz, DES, fl, DES, cs);
	else if (flag_r == EXIT_SUCCESS && fg_t == EXIT_SUCCESS)
		bsdc(sz, ASC, fl, ASC, cs);
	else if (flag_r == EXIT_SUCCESS)
		rbs(fl, cs);
	else
		bsort(fl, cs);
}
