#include "signals.h"

/**
 * handle_signal - Function to set the signal handler
 * Return: -1 on error or 0 when success
 */
int handle_signal(void)
{
	/* Set the handler sor SIGINT or CTRL-C */
	if (signal(SIGINT, hdl_ctrl_c) == SIG_ERR)
		return (-1);
	return (0);
}

/**
 * hdl_ctrl_c - Function that catch the signal CTRL-C or SIGINT
 * @signal: the signal
 * Return: Nothing
 */
void hdl_ctrl_c(int signal)
{
	printf("Gotcha! [<%d>]\n", signal);
}
