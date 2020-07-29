#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "_getline.h"

/**
 * _getline - Basic getline functionality.
 * @fd: File Descriptor
 * Return: Returns a null-terminated string that does not include the newline
 * character, or NULL if there is a reading failure or reach EOF.
 */
char *_getline(const int fd)
{
static char buffst[256];
char *nl = NULL, *cr = NULL, *buffer, buf[READ_SIZE + 1];
ssize_t qty;
size_t iter = 0;

	buffer = malloc((255 + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	strcpy(buffer, buffst);

	while ((qty = read(fd, (void *)buf, READ_SIZE)) > 0)
	{
		buf[qty] = '\0';
		nl = _strchr(buf, 10), cr = _strchr(buf, 12);
		if (nl == NULL && cr == NULL)
		{
			strcpy((buffer + iter), buf);
			iter += qty;
		}
		else
		{
			if (nl != NULL)
			{	*nl = '\0', nl++;
				strcpy((buffer + iter), buf);
				strcpy(buffst, nl);
			}
			else
			{	*cr = '\0', cr++;
				strcpy((buffer + iter), buf);
				strcpy(buffst, cr);
			}
			break;
		}
	}

	if (qty == -1 || qty == 0)
	{	free(buffer);
		return (NULL);
	}
	return (buffer);
}

/**
 * _strchr - Returns a pointer to the first occurence of c char in string s.
 * @s: The string
 * @c: The char
 * Return: A pointer to the position or NULL
 */
char *_strchr(char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}

	return (NULL);
}
