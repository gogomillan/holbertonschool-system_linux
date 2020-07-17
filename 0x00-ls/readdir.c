#include "hls.h"

char *geterrmsg(int errcode);

/**
 * _readdir - Reading and printing the files content in a directory
 *
 * @dirs: The list of directories
 * @opts: The list of options
 *
 * Return: EXIT_SUCCESS when success, EXIT_FAILURE in other case
 */
int _readdir(char **dirs, char **opts)
{
DIR *dir;						/* Structure to the directory */
char bufmsg[128];				/* Buffer for messages*/
char dirprnctrl, fileprnctrl;	/* Colflow when print directory name & content */

	(void)opts;
	if (dirs[1] != NULL)
		dirprnctrl = TRUE;
	else
		dirprnctrl = FALSE;

	if (dirs == NULL)
		return (EXIT_FAILURE);

	while (*dirs != NULL)
	{
		dir = opendir(*dirs);
		if (dir == NULL)
		{
			sprintf(bufmsg, "ls: %s: ", geterrmsg(errno));
			fprintf(stderr, bufmsg, *dirs);
			fprintf(stderr, "%s\n", strerror(errno));
			return (EXIT_FAILURE);
		}
		if (dirprnctrl)
			printf("%s:\n", *dirs);

		fileprnctrl = FALSE;
		while ((read = readdir(dir)) != NULL)
			if (strncmp(read->d_name, ".", 1) != 0)
			{
				if (fileprnctrl)
					printf("  ");
				printf("%s", read->d_name);
				fileprnctrl = TRUE;
			}
		if (fileprnctrl)
			printf("\n");

		closedir(dir);
		dirs++;
		if (dirprnctrl && *dirs != NULL)
			printf("\n");
	}

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
