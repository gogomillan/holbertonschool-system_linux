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
char *buffst; /*static char buffst[BUFF_SIZE];*/
char *nl = NULL, *buffer, buf[READ_SIZE + 1];
ssize_t qty;
size_t iter = 0;
listfd_t *node;

	while ((node = nodelistfd(fd)) == NULL)
		return (NULL);

	buffst = node->buffst;
	buffer = malloc((BUFF_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	strcpy(buffer, buffst), buffst[0] = '\0', nl = _strchr(buffer, 10);
	if (nl != NULL)
	{	*nl = '\0', nl++;
		strcpy(buffst, nl);
		return (buffer);
	}
	iter = _strlen(buffer);

	while ((qty = read(fd, (void *)buf, READ_SIZE)) > 0)
	{
		buf[qty] = '\0', nl = _strchr(buf, 10);
		if (nl == NULL)
			strcpy((buffer + iter), buf), iter += qty;
		else
		{	*nl = '\0', nl++;
			strcpy((buffer + iter), buf);
			strcpy(buffst, nl);
			break;
		}
	}

	if ((qty == -1 || qty == 0) && _strlen(buffer) == 0)
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

/**
 * _strlen - Returns the leng of a string
 * @s: The string
 * Return: The lenght
 */
size_t _strlen(char *s)
{
size_t iter = 0;

	while (*s != '\0')
		s++, iter++;
	return (iter);
}

/**
 * nodelistfd - Put or Get a node from a singly liked list for fd.
 * @fd: The file descriptor
 * Return: A pointer to a node from listfd_s or NULL if failure.
 *
 * Description: This function has two functionalities in one. The first one is
 * that alows add the fd to the list if not exists or return the element if
 * exists in the linked list.
 */
listfd_t *nodelistfd(int fd)
{
static listfd_t *head;
listfd_t *node, *curr;

	/* If -1 we should free the memory */
	if (fd == -1)
	{
		curr = head;
		while (curr != NULL)
			node = curr, curr = curr->next, free(node);
		head = NULL;
		return (NULL);
	}
	/* Creating the possible new node */
	node = malloc(sizeof(listfd_t));
	if (node == NULL)
		return (NULL);
	node->fd = fd, node->buffst[0] = '\0', node->next = NULL;
	/* Evaluating the head if not exists to created */
	if (head == NULL)
	{
		head = node;
		return (head);
	}
	curr = head;
	/* Looking for a possible element */
	while (curr != NULL)
		if (curr->fd != fd)
			curr = curr->next;
		else
			break;
	/* If exists return it */
	if (curr != NULL)
	{	free(node);
		return (curr);
	}
	/* If not exist add it and return it */
	curr->next = node;
	return (node);
}
