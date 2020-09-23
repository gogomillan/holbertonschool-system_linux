## :memo: x86 Assembly - libASM
\[ [Back](../../..#readme) \]
\[ [Concepts](#Concepts--arrow_up-) \]
\[ [Requirements](#Requirements--arrow_up-) \]
\[ [Tasks](#Tasks--arrow_up-) \]

### Concepts \[ [:arrow_up:](#memo-heap-insert) \]
- The differences between Intel and AT&T syntaxes
- The different x86 GPR
- The different flag registers
- What is a stack frame
- How to setup a stack frame
- How to call a function
- How to make a system call
- How to pass parameters to a function
- How to retrieve parameters

### Requirements \[ [:arrow_up:](#memo-heap-insert) \]
- Linux Ubuntu 14.04 LTS
- NASM version 2.10.09
- gcc (Ubuntu 4.8.4-2ubuntu1~14.04.4) 4.8.4

### Tasks \[ [:arrow_up:](#memo-heap-insert) \]

#### Task 0: strlen \[ [:arrow_up:](#memo-heap-insert) \]
Write a copycat of the function strlen(3), in x86-64 Assembly
- Prototype when used in C: size\_t asm\_strlen(const char \*str);

**Example:**
```bash
alex@~/0x05-libasm$ cat 0-main.c 
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1  "Holberton School"
#define S2  ""
#define S3  "\0"

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    assert(strlen(S1) == asm_strlen(S1));
    assert(strlen(S2) == asm_strlen(S2));
    assert(strlen(S3) == asm_strlen(S3));

    printf("All good!\n");
    return (EXIT_SUCCESS);
}
alex@~/0x05-libasm$ gcc -Wall -Wextra -Werror -pedantic -g3 -c -o 0-main.o 0-main.c
alex@~/0x05-libasm$ nasm -f elf64 -o 0-strlen.o 0-strlen.asm
alex@~/0x05-libasm$ gcc -o 0-strlen 0-main.o 0-strlen.o
alex@~/0x05-libasm$ ./0-strlen 
All good!
alex@~/0x05-libasm$ 
```
**File:**
\[ [0-strlen.asm](0-strlen.asm) \]

\[ [Back](../../..#readme) \] \[ [:arrow_up:](#memo-heap-insert) \]
