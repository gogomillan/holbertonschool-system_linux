#include "signals.h"

/**
* current_handler_sigaction - function that retrieves the current handler of
* the signal SIGINT
* Return: pointer to the current handler of SIGINT, or NULL on failure
*/
void (*current_handler_sigaction(void))(int)
{
	struct sigaction oldact;

	if (sigaction(SIGINT, NULL, &oldact) == -1)
		return (NULL);

	return (oldact.sa_handler);
}
