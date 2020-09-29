#include "signals.h"

/**
* pid_exist -  tests if a process exists, given its PID
* @pid: process id
* Return: 1 on succes, 0 otherwise
*/
int pid_exist(pid_t pid)
{
	if (kill(pid, 0) == 0)
		return (1);
	return (0);
}
