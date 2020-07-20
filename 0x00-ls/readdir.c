#include "hls.h"

void set_format(char *opt);
int _prndir(char *dirs, char dirprnctrl);
int _prnfiles(char **files, char *dirprnctrl);
char *geterrmsg(char *path);
int _format(char *opt, char oper);

/**
 * _readdir - Reading and printing the files content in a directory
 *
 * @fils: The list of files
 * @dirs: The list of directories
 * @opts: The list of options
 *
 * Return: EXIT_SUCCESS when success, EXIT_FAILURE in other case
 */
int _readdir(char **fils, char **dirs, char **opts)
{
char retd = EXIT_SUCCESS, retf = EXIT_SUCCESS;	/* Return */
char dirprnctrl = FALSE;		/* Colflow when print directory name & content */

	if (fils == NULL || dirs == NULL)		/* If no dirs and files, nothing */
		return (EXIT_FAILURE);

	while (*opts != NULL)					/* Set the options, if there are */
	{
		_format(*opts, PUT);
		opts++;
	}

	if (*fils != NULL)						/* If files, then print them */
	{	retf = _prnfiles(fils, &dirprnctrl);
		if (*dirs != NULL && dirprnctrl == EXIT_SUCCESS)
			printf("\n");
		dirprnctrl = TRUE;
	}

	if (dirs[1] != NULL || dirprnctrl == TRUE)
		dirprnctrl = TRUE;	/* If there are more than one dir to print */
	else
		dirprnctrl = FALSE;	/* If there is only the "." dir to print */

	while (*dirs != NULL)					/* If dirs, then print them */
	{	retd = _prndir(*dirs, dirprnctrl);
		dirs++;
		if (dirprnctrl && retd == EXIT_SUCCESS && *dirs != NULL)
			printf("\n");
	}

	return ((retf >= retd) ? retf : retd);	/* If error on files or dirs prn */
}

/**
 * _prnfiles - Print the files in args
 *
 * @files: Path to the filenames
 * @dirprnctrl: Control printing for files
 *
 * Return: EXIT_SUCCESS if alright, EXIT_FAILURE other case
 */
int _prnfiles(char **files, char *dirprnctrl)
{
char bufmsg1[128], bufmsg2[128];	/* Buffer for messages*/
char fileprnctrl = FALSE, ret = EXIT_SUCCESS;	/* Colflow when print */
struct stat sb;

	*dirprnctrl = EXIT_FAILURE;
	while (*files != NULL)
	{
		if (stat(*files, &sb) == -1)
		{
			sprintf(bufmsg1, "hls: %s", geterrmsg(*files));
			sprintf(bufmsg2, bufmsg1, *files);
			perror(bufmsg2);
			ret = EXIT_FAILURE;
		}
		else
		{
			if (fileprnctrl)
			{
				if (_format("1", GET) == EXIT_SUCCESS)
					printf("\n");
				else
					printf("  ");
			}
			printf("%s", *files);
			fileprnctrl = TRUE;
			*dirprnctrl = EXIT_SUCCESS;
		}
		files++;
	}
	if (fileprnctrl)
		printf("\n");
	return (ret);
}

/**
 * _prndir - Print the files content in a dir
 *
 * @dirs: Path to the dir
 * @dirprnctrl: Print dir name TRUE or FALSE
 *
 * Return: EXIT_SUCCESS if alright, EXIT_FAILURE other case
 */
int _prndir(char *dirs, char dirprnctrl)
{
char bufmsg1[128], bufmsg2[128];	/* Buffer for messages*/
DIR *dir;							/* Structure to the directory */
char fileprnctrl, flag_a, flag_A;	/* Colflow when print directory */

	dir = opendir(dirs);						/* Open the dir */
	if (dir == NULL)							/* Verify what happened */
	{
		sprintf(bufmsg1, "hls: %s", geterrmsg(dirs));
		sprintf(bufmsg2, bufmsg1, dirs);
		perror(bufmsg2);
		return (EXIT_FAILURE);
	}
	if (dirprnctrl)								/* If print dir name is neded */
		printf("%s:\n", dirs);

	fileprnctrl = FALSE;
	while ((r_entry = readdir(dir)) != NULL)	/* For each dir entrance */
	{	flag_a = _format("a", GET);
		flag_A = _format("A", GET);
		if ((flag_A == EXIT_SUCCESS &&	/* If opt A and not dir . or .. */
			_strcmp(r_entry->d_name, ".") != 0 &&
			_strcmp(r_entry->d_name, "..") != 0) ||
			flag_a == EXIT_SUCCESS ||	/* Or opt a */
			r_entry->d_name[0] != '.')	/* Or dir name starting without . */
		{
			if (fileprnctrl)			/* File name sepparator */
			{
				if (_format("1", GET) == EXIT_SUCCESS)
					printf("\n");
				else
					printf("  ");
			}
			printf("%s", r_entry->d_name);
			fileprnctrl = TRUE;
		}
	}
	if (fileprnctrl)
		printf("\n");

	closedir(dir);
	return (EXIT_SUCCESS);
}

/**
 * geterrmsg - Get the message for the errcode
 *
 * @path: The path to verify
 *
 * Return: A string with the error message
 */
char *geterrmsg(char *path)
{
struct stat sb;

	if (stat(path, &sb) == -1)
		return ("cannot access %s");

	return ("cannot open directory %s");
}

/**
 * _format - Set the ls print format
 *
 * @opt: the option
 * @oper: the operation [PUT | GET]
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int _format(char *opt, char oper)
{
static char op[128] = { '\0' };
int iter = 0, flag = TRUE;

	if (oper == PUT)	/* Put the flag from var opt */
	{
		for (iter = 0; op[iter] != '\0'; iter++)
		{
			if (op[iter] == 'A' && *opt == 'a')
			{	op[iter] = *opt, flag = FALSE;
			}
			if (op[iter] == 'a' && *opt == 'A')
				flag = FALSE;
			if (op[iter] == '1' && *opt == 'l')
			{	op[iter] = *opt, flag = FALSE;
			}
			if (op[iter] == 'l' && *opt == '1')
				flag = FALSE;
		}
		if (flag)
		{	op[iter] = *opt, iter++, op[iter] = '\0';
		}
		return (EXIT_SUCCESS);
	}
	else if (oper == GET)	/* Try get the var opt */
	{
		for (iter = 0; op[iter] != '\0'; iter++)
			if (op[iter] == *opt)
				return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	else					/* When other case */
		return (EXIT_FAILURE);
}
