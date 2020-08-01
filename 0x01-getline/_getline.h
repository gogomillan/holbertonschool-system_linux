#ifndef GOGOMILLAN
#define GOGOMILLAN

#define READ_SIZE 4
#define BUFF_SIZE 512

#define TOCR 0
#define TONU 1

/**
 * struct listfd_s - singly linked list for fd
 * @fd: The file descriptor associated
 * @buffst: The buffer static associated to fd
 * @next: The pointer to the next node
 */
typedef struct listfd_s
{
	int fd;
	char buffst[BUFF_SIZE];
	struct listfd_s *next;
} listfd_t;

char *_getline(const int fd);

char *_strchr(char *s, int c);
size_t _strlen(char *s);
listfd_t *nodelistfd(int fd);
void mrknll(char *str, size_t len, char oper);

#endif
