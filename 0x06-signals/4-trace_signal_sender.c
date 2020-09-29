#include "signals.h"

/**
 * trace_signal_sender - function that defines a handler for the signal SIGQUIT
 * (Control-\ in a shell)
 * Return: -1 on error or 0 when success
 */
int trace_signal_sender(void)
{
	struct sigaction act;

	/* Set up the structure to specify the new action. */
	memset(&act, '\0', sizeof(act));
	act.sa_sigaction = hdl_sender;
	act.sa_flags = SA_SIGINFO;

	/* Set the handler sor SIGINT or CTRL-C */
	return (sigaction(SIGQUIT, &act, NULL));
}

/**
 * hdl_sender - Function that catch the signal CTRL-C or SIGINT
 * @sig: the signal
 * @siginfo: the signal's info
 * @context: the signal's context
 * Return: Nothing
 */
void hdl_sender(int sig, siginfo_t *siginfo, void *context)
{
	(void)sig;
	(void)context;
	printf("SIGQUIT sent by %d\n", (int) siginfo->si_pid);
}
