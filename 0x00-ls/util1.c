#include "hls.h"

/**
 * intlen - Return the lenght in digits for an integer
 *
 * @vr: The value
 *
 * Return: Number of digits
 */
int intlen(int vr)
{
int cont = 1, digit = 1;

	while ((vr / (digit * 10)) > 0)
		digit *= 10, cont++;
	return (cont);
}

/**
 * _strlen - Return the lenght of string
 *
 * @str: The string
 *
 * Return: Number of digits
 */
int _strlen(char *str)
{
int cont = 0;

	while (*str++ != '\0')
		cont++;
	return (cont);
}

/**
 * _guid - Return the string according to the uid
 *
 * @st_uid: User id
 * @susr: String to store the user name
 *
 * Return: Pointer to the user name
 */
char *_guid(uid_t st_uid, char *susr)
{
struct passwd *usr;

	usr = getpwuid(st_uid); /* Get the user name from the user id */
	if (usr != NULL)
		sprintf(susr, "%s%c", usr->pw_name, '\0');	/* Buffer for user name  */
	else
		sprintf(susr, "%d%c", (int)st_uid, '\0');	/* Buff for usr code */

	return (susr);
}

/**
 * _ggid - Return the string according to the gid
 *
 * @st_gid: Group id
 * @sgrp: String to store the grup name
 *
 * Return: Pointer to the user name
 */
char *_ggid(gid_t st_gid, char *sgrp)
{
struct group *grp;

	grp = getgrgid(st_gid); /* Get the group name from the group id */
	if (grp != NULL)
		sprintf(sgrp, "%s%c", grp->gr_name, '\0');	/* Buffer for user name  */
	else
		sprintf(sgrp, "%d%c", (int)st_gid, '\0');	/* Buff for usr code */

	return (sgrp);
}

/**
 * dtom - Directory content to memory
 *
 * @dirs: The path to the dir
 * @t_fls: Total files
 *
 * Return: Pointer to the list of files ordered
 */
char **dtom(char *dirs, size_t t_fls)
{
char flag_a, flag_A, **files, **tmp;	/* Buffers */
DIR *dir;								/*  Structure to the directory */
size_t iter;

	files = malloc((t_fls + 1) * sizeof(char *));
	if (files == NULL)
		return (NULL);
	for (iter = 0; iter < (t_fls + 1); iter++)
		*(files + iter) = NULL;

	dir = opendir(dirs);							/* Open the dir			 */
	flag_a = _format("a", GET), flag_A = _format("A", GET), tmp = files;
	while ((r_entry = readdir(dir)) != NULL)		/* For each dir entrance */
		if ((flag_A == EXIT_SUCCESS &&	/* If  opt A and not dir "." or ".." */
			_strcmp(r_entry->d_name, ".", NOCASE) != 0 &&
			_strcmp(r_entry->d_name, "..", NOCASE) != 0) ||
			flag_a == EXIT_SUCCESS ||	/* Or  option "a" is set             */
			r_entry->d_name[0] != '.')	/* Or  dir name starting without "." */
		{
			*tmp = malloc((_strlen(r_entry->d_name) + 2) * sizeof(char));
			if (*tmp == NULL)
			{
				while (*files++ != NULL)
					free(*files);
				free(files);
			}
			sprintf(*tmp, "%s%c", r_entry->d_name, '\0'), tmp++;
		}
	closedir(dir);
	if (_format("r", GET) == EXIT_SUCCESS)
		rbs(files, NOCASE);
	else
		bsort(files, NOCASE);

	return (files);
}
