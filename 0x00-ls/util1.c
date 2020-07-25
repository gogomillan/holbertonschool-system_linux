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
char fg_a, fg_A, flag_r, flag_S, fg_t, **files, **tmp, **sizes, **size;
DIR *dir;							/*  Structure to the directory */

	if (_gmfiles(&files, &sizes, t_fls) == EXIT_FAILURE)
		return (NULL);
	dir = opendir(dirs);							/* Open the dir			 */
	fg_a = _format("a", GET), fg_A = _format("A", GET), fg_t = _format("t", GET);
	tmp = files, size = sizes;
	while ((r_entry = readdir(dir)) != NULL)					/* For each dir entrance */
		if ((fg_A == EXIT_SUCCESS &&				/* If opt A and not dir "." or ".." */
			_strcmp(r_entry->d_name, ".", NOCASE) != 0 &&
			_strcmp(r_entry->d_name, "..", NOCASE) != 0) ||
			fg_a == EXIT_SUCCESS || r_entry->d_name[0] != '.')	/* Or opt a Or dirname */
		{
			*tmp = malloc((_strlen(r_entry->d_name) + 2) * sizeof(char));
			*size = malloc((20 + 2) * sizeof(char));
			if (*tmp == NULL || *size == NULL)
			{
				_freedp(files), _freedp(sizes);
				return (NULL);
			}
			sprintf(*tmp, "%s%c", r_entry->d_name, '\0'), tmp++;
			if (fg_t == EXIT_SUCCESS)
				sprintf(*size, "%0*ld%c", 20, _gtime(dirs, r_entry->d_name), '\0');
			else
				sprintf(*size, "%0*d%c", 20, (int)_gsize(dirs, r_entry->d_name), '\0');
			size++;
		}
	closedir(dir), flag_r = _format("r", GET), flag_S = _format("S", GET);
	flag_S = (flag_S == EXIT_SUCCESS) ? flag_S : fg_t;
	if (flag_r == EXIT_SUCCESS && flag_S != EXIT_SUCCESS)
		rbs(files, NOCASE);
	else if (flag_r != EXIT_SUCCESS && flag_S == EXIT_SUCCESS)
		bsdc(sizes, DES, files, ASC, NOCASE);
	else if (flag_r == EXIT_SUCCESS && flag_S == EXIT_SUCCESS)
		bsdc(sizes, ASC, files, DES, NOCASE);
	else
		bsort(files, NOCASE);
	_freedp(sizes);
	return (files);
}
