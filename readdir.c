#include "hls.h"

char *geterrmsg(int errcode);

/**
 * _readdir - Reading and printing the files content in a directory
 *
 * @dir_name: The name of the directory
 *
 * Return: EXIT_SUCCESS when success, EXIT_FAILURE in other case
 */
int _readdir(char *dir_name)
{
	DIR *dir;            /* Structure pointing to the directory */
	struct dirent *read; /* Structure pointing to the directory entry */
	char bufmsg[128];    /* Buffer for messages */
	char prnctrl;        /* Control flow when print directory content */

	dir = opendir(dir_name);
	if (dir == NULL)
	{
		sprintf(bufmsg, "ls: %s: ", geterrmsg(errno));
		fprintf(stderr, bufmsg, dir_name);
		fprintf(stderr, "%s\n", strerror(errno));
		return (EXIT_FAILURE);
	}

	prnctrl = FALSE;
	while ((read = readdir(dir)) != NULL)
	{
		if (prnctrl)
			printf("  ");
		printf("%s", read->d_name);
		prnctrl = TRUE;
	}
	if (prnctrl)
		printf("\n");

	closedir(dir);
	return (EXIT_SUCCESS);
}

/**
 * geterrmsg - Get the message for the errcode
 *
 * @errcode: The errcode from the OS
 *
 * Return: A string with the error message
 */
char *geterrmsg(int errcode)
{
	if (errcode == EACCES)
		return ("cannot open directory %s");
	else if (errcode == ENOENT)
		return ("cannot access %s");
	else
		return ("cannot open directory %s");
}
