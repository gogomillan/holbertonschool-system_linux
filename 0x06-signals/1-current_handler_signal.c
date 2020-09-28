#include "signals.h"

/**
 * current_handler_signal - function that retrieves the current handler of the
 * signal SIGINT
 * Return - Return the function nandler
 */
void (*current_handler_signal(void))(int)
{
	void (*handler)(int);

	handler = signal(SIGINT, NULL);
	signal(SIGINT, handler);

	return (handler);
}
