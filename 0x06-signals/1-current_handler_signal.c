#include "signals.h"

void (*current_handler_signal(void))(int)
{
	void (*handler)(int);

	handler = signal(SIGINT, NULL);
	signal(SIGINT, handler);

	return (handler);
}
