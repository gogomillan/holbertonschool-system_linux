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
DIR *dir;										/* Structure to the directory */
char bufmsg1[128], bufmsg2[128], ret = EXIT_SUCCESS;	/* Buffer for messages*/
char dirprnctrl, fileprnctrl;	/* Colflow when print directory name & content */

	(void)opts;
	if (dirs == NULL)
		return (EXIT_FAILURE);

	if (dirs[1] != NULL)
		dirprnctrl = TRUE;
	else
		dirprnctrl = FALSE;

	while (*dirs != NULL)
	{
		dir = opendir(*dirs);
		if (dir == NULL)
		{
			sprintf(bufmsg1, "hls: %s", geterrmsg(errno));
			sprintf(bufmsg2, bufmsg1, *dirs);
			perror(bufmsg2);
			ret = EXIT_FAILURE;
			dirs++;
			continue;
		}
		if (dirprnctrl)
			printf("%s:\n", *dirs);

		fileprnctrl = FALSE;
		while ((r_entry = readdir(dir)) != NULL)
			if (r_entry->d_name[0] != '.')
			{
				if (fileprnctrl)
					printf("  ");
				printf("%s", r_entry->d_name);
				fileprnctrl = TRUE;
			}
		if (fileprnctrl)
			printf("\n");

		closedir(dir);
		dirs++;
		if (dirprnctrl && *dirs != NULL)
			printf("\n");
	}

	return (ret);
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
