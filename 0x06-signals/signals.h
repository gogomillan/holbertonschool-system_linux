#ifndef gogomillan
#define gogomillan

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

int handle_signal(void);
void hdl_ctrl_c(int signal);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
void hdl_sender(int sig, siginfo_t *siginfo, void *context);

#endif  /* gogomillan */
