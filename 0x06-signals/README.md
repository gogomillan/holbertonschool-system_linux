## :memo: C - Signals
\[ [Back](../../..#readme) \]
\[ [Concepts](#Concepts--arrow_up-) \]
\[ [Requirements](#Requirements--arrow_up-) \]
\[ [Tasks](#Tasks--arrow_up-) \]
\[ [0](#Task-0-handle-signal--arrow_up-) \]
\[ [1](#Task-1-current-handler-signal--arrow_up-) \]

### Concepts \[ [:arrow_up:](#memo-c---signals) \]
- What is a signal
- Why do they exist
- When are they delivered and by whom
- What are the default actions of signals
- How to set up a handler for a signal
- How to send signals
- What signals cant be caught


### Requirements \[ [:arrow_up:](#memo-c---signals) \]
- Linux Ubuntu 14.04 LTS
- gcc (Ubuntu 4.8.4-2ubuntu1~14.04.4) 4.8.4


### Tasks \[ [:arrow_up:](#memo-c---signals) \]

#### Task 0: Handle signal \[ [:arrow_up:](#memo-c---signals) \]
Write a function that set a handler for the signal SIGINT
- Prototype: int handle_signal(void);
- Your function must return 0 on success, or -1 on error
- The program should print Gotcha! [\<signum\>] followed by a new line, every time Control-C is pressed (See example below)
  - where \<signum\> must be replaced with the signal number that was caught
- sigaction(2) is not allowed


**Example:**
```bash
alex@~/0x06-signals$ cat 0-main.c
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "signals.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    int i;

    if (handle_signal() == -1)
    {
        printf("Failure\n");
        return (EXIT_FAILURE);
    }
    for (i = 0; ; i++)
    {
        printf("[%d] Wait for it ...\n", i);
        sleep(1);
    }
    return (EXIT_SUCCESS);
}
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 0-main.c 0-handle_signal.c -o 0-handle_signal
alex@~/0x06-signals$ ./0-handle_signal 
[0] Wait for it ...
[1] Wait for it ...
[2] Wait for it ...
^CGotcha! [2]
[3] Wait for it ...
^CGotcha! [2]
[4] Wait for it ...
[5] Wait for it ...
^CGotcha! [2]
[6] Wait for it ...
[7] Wait for it ...
^CGotcha! [2]
[8] Wait for it ...
[9] Wait for it ...
^\Quit (core dumped)
alex@~/0x06-signals$
```
**File:**
\[ [0-handle_signal.c](0-handle_signal.c) \]

#### Task 1: Current handler - signal \[ [:arrow_up:](#memo-c---signals) \]
Write a function that retrieves the current handler of the signal SIGINT
- Prototype: void (\*current_handler_signal(void))(int);
- Your function returns a pointer to the current handler of SIGINT, or NULL on
failure
- You are not allowed to use sigaction(2)
- The handler must be unchanged after calling your function

**Example:**
```bash
alex@~/0x06-signals$ cat 1-main.c 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "signals.h"

/* Our functions */
void print_hello(int);
void set_print_hello(void);

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    void (*handler)(int);
    int i;

    handler = current_handler_signal();
    printf("Address of the current handler: %#lx\n", (unsigned long int)handler);

    /* Set 'print_hello()` as the handler for SIGINT */
    set_print_hello();

    handler = current_handler_signal();
    printf("Address of the 'print_hello' function: %#lx\n", (unsigned long int)&print_hello);
    printf("Address of the current handler: %#lx\n", (unsigned long int)handler);

    for (i = 0; ; i++)
    {
        printf("[%d] Wait for it ...\n", i);
        sleep(1);
    }
    return (EXIT_SUCCESS);
}
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 1-main.c 1-set_print_hello.c 1-current_handler_signal.c -o 1-current_handler_signal
alex@~/0x06-signals$ ./1-current_handler_signal
Address of the current handler: 0
Address of the 'print_hello' function: 0x4006da
Address of the current handler: 0x4006da
[0] Wait for it ...
[1] Wait for it ...
^CHello :)
[2] Wait for it ...
^CHello :)
[3] Wait for it ...
[4] Wait for it ...
^CHello :)
[5] Wait for it ...
^\Quit (core dumped)
alex@~/0x06-signals$
```
**File:**
\[ [1-current_handler_signal.c](1-current_handler_signal.c) \]


\[ [Back](../../..#readme) \] \[ [:arrow_up:](#memo-c---signals) \]
