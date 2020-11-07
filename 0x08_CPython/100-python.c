#include <Python.h>

/**
 * print_python_int - prints Python integers
 * @p: PyObject int
 */
void print_python_int(PyObject *p)
{
	Py_ssize_t size, i;
	digit *digit;
	unsigned long value = 0;

	/* Error checking */
	if (!p || !PyLong_Check(p))
	{
		printf("Invalid Int Object\n");
		return;
	}

	size = ((PyVarObject *)(p))->ob_size;
	digit = ((PyLongObject *)(p))->ob_digit;

	/* Check for u_int overflow in C */
	if (abs(size) > 3 || (abs(size) == 3 && digit[2] > 15))
	{
		printf("C unsigned long int overflow\n");
		return;
	}

	/* Create int value from string */
	for (i = 0; i < abs(size); i++)
	{
		value += digit[i] * (1L << (i * PyLong_SHIFT));
	}

	if (size < 0)
		
putchar('-');

	printf("%lu\n", value);
}
