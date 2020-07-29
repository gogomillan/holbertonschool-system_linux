#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "_getline.h"

/**
 * _getline - Basic getline functionality.
 * @fd: File Descriptor
 * Return: Returns a null-terminated string that does not include the newline
 * character, or NULL if there is a reading failure or reach EOF.
 */
char *_getline(const int fd)
{
char *buffer, buf[2];
ssize_t qty;
size_t iter = 0;

	buffer = malloc((BUFF_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);

	while ((qty = read(fd, (void *)buf, READ_SIZE)) > 0)
	{
		if (buf[0] != 10 && buf[0] != 12)
			buffer[iter++] = buf[0];
		else
			break;
	}
	buffer[iter] = '\0';

	if (qty == -1 || qty == 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
