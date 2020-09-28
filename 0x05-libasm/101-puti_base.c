#include <stdlib.h>
#include <stdio.h>

#include "libasm.h"

/*
asm_putc('H')
asm_strlen(S1)
*/

size_t asm_puti_base(int n, const char *base)
{
	size_t b = asm_strlen((char *)base);
	int ret = 0;

	if ((n / (int)b) == 0)
	{
		if (n < 0)
		{
			asm_putc('-');
			n = -n;
		}
		asm_putc(base[n % (int)b]);
		return (1);
	}
	ret = asm_puti_base((n / (int)b), base);
	ret += asm_putc(base[n % (int)b]);

	return (ret);
}
