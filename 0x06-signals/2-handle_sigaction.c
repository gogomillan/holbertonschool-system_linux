#include "signals.h"

/**
 * handle_sigaction - function that set a handler for the signal SIGINT
 * Return: -1 on error or 0 when success
 */
int handle_sigaction(void)
{
	struct sigaction act;

	/* Set up the structure to specify the new action. */
	memset(&act, '\0', sizeof(act));
	act.sa_handler = hdl_ctrl_c;
	act.sa_flags = 0;

	/* Set the handler sor SIGINT or CTRL-C */
	return (sigaction(SIGINT, &act, NULL));
}

/**
 * hdl_ctrl_c - Function that catch the signal CTRL-C or SIGINT
 * @signal: the signal
 * Return: Nothing
 */
void hdl_ctrl_c(int signal)
{
	printf("Gotcha! [%d]\n", signal);
	fflush(stdout);
}
