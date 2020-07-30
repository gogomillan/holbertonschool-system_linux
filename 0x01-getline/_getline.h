#ifndef GOGOMILLAN
#define GOGOMILLAN

#define READ_SIZE 4
#define BUFF_SIZE 512

char *_getline(const int fd);

char *_strchr(char *s, int c);
size_t _strlen(char *s);

/**
 * struct listfd_s - singly linked list for fd
 * @fd: The file descriptor associated
 * @bufferst: The buffer static associated to fd
 */
typedef struct listfd_s
{
	int fd;
	char *bufferst[BUFF_SIZE];
} listfd_t;

#endif
