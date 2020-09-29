#include "signals.h"

/**
* handler - The handler
* @signal: The signal code
* Return: nothing
*/
void handler(int signal)
{
	printf("Caught %d\n", signal);
}

/**
* main - wait until the signal sigint be executed
* Return: 0 on success
*/
int main(void)
{
	struct sigaction act;

	/* Set up the structure to specify the new action. */
	memset(&act, '\0', sizeof(act));
	act.sa_handler = handler;
	act.sa_flags = SA_SIGINFO;

	sigaction(SIGINT, &act, NULL);
	pause();
	printf("Signal received\n");
	return (EXIT_SUCCESS);
}
