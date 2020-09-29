#ifndef gogomillan
#define gogomillan

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int handle_signal(void);
void hdl_ctrl_c(int signal);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);

#endif  /* gogomillan */
