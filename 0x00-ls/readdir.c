#include "hls.h"

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
		_format(*opts, PUT), opts++;

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
char bufmsg1[128], bufmsg2[128], flag_1, flag_l;/* Buffer for messages*/
char fileprnctrl = FALSE, ret = EXIT_SUCCESS;	/* Colflow when print */
/**
 * stat - struct for file information
 */
struct stat sb;

	*dirprnctrl = EXIT_FAILURE;
	flag_1 = _format("1", GET), flag_l = _format("l", GET);
	while (*files != NULL)							/* For each file */
	{
		if (lstat(*files, &sb) == -1)	/* If the path has a problem */
		{
			sprintf(bufmsg1, "hls: %s", geterrmsg(*files));
			sprintf(bufmsg2, bufmsg1, *files), perror(bufmsg2);
			ret = EXIT_FAILURE;	/* Memorize errors to return */
		}
		else								/* When path is right    */
		{
			if (fileprnctrl)
			{
				if (flag_l == EXIT_SUCCESS || flag_1 == EXIT_SUCCESS)
					printf("\n");
				else
					printf("  ");
			}
			if (flag_l == EXIT_SUCCESS)
				printf("%s", frmt_l("", *files));
			else
				printf("%s", *files);
			fileprnctrl = TRUE;
			*dirprnctrl = EXIT_SUCCESS;	/* Memorize if print */
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
char buff1[128], buff2[128], flag_1, flag_l, fpc, **fls, **tmp;
DIR *dir;									/* Structure to the directory */
size_t t_fls;								/* Total files in a directory */

	dir = opendir(dirs);						/* Open the dir */
	if (dir == NULL)							/* Verify what happened */
	{	sprintf(buff1, "hls: %s", geterrmsg(dirs));
		sprintf(buff2, buff1, dirs), perror(buff2);
		return (EXIT_FAILURE);
	}
	if (dirprnctrl)								/* If print dir name is neded */
		printf("%s:\n", dirs);
	closedir(dir);

	flag_1 = _format("1", GET), flag_l = _format("l", GET);
	fpc = FALSE, _dstat(dirs, W_INIT), t_fls = _dstat(dirs, N_FL);
	fls = dtom(dirs, t_fls), tmp = fls;
	while (*tmp != NULL)							/* For each file name */
	{
		if (fpc)				/* File name sepparator */
		{
			if (flag_l == EXIT_SUCCESS || flag_1 == EXIT_SUCCESS)
				printf("\n");	/* Separator for -1 option  */
			else
				printf("  ");	/* Separator for others    */
		}
		if (flag_l == EXIT_SUCCESS)
			printf("%s", frmt_l(dirs, *tmp));
		else
			printf("%s", *tmp);
		fpc = TRUE, tmp++;
	}													/* End while for dir */
	if (fpc)
		printf("\n");

	tmp = fls;
	while (*tmp != NULL)
		free(*tmp++);
	free(fls);
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

	if (lstat(path, &sb) == -1)
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
				op[iter] = *opt, flag = FALSE;
			if (op[iter] == 'a' && *opt == 'A')
				flag = FALSE;
			if (op[iter] == '1' && *opt == 'l')
				op[iter] = *opt, flag = FALSE;
			if (op[iter] == 'l' && *opt == '1')
				flag = FALSE;
		}
		if (flag)
			op[iter] = *opt, iter++, op[iter] = '\0';
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
