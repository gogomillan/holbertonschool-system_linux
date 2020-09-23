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
 * @t_drs: Total subdirectories
 *
 * Return: Pointer to the list of files ordered
 */
char ***dtom(char *dirs, size_t t_fls, size_t t_drs)
{
char f_a, f_A, f_t, f_R, *dn, **fls, **fl, **szs, **sz, **ldrs, **ldr, ***ret;
DIR *dir;				/*  Structure to the directory */
	if (_gmfiles(&fls, &szs, t_fls, &ldrs, t_drs) == EXIT_FAILURE)	/* G mem */
		return (NULL);
	f_a = _format("a", GET), f_A = _format("A", GET), f_t = _format("t", GET);
	dir = opendir(dirs), fl = fls, sz = szs, ldr = ldrs, f_R = _format("R", GET);
	while ((r_entry = readdir(dir)) != NULL)					/* For each dir entrance */
		if ((f_A == EXIT_SUCCESS && _strcmp(r_entry->d_name, ".", NOCASE) != 0 &&
			_strcmp(r_entry->d_name, "..", NOCASE) != 0) ||	/* Opt A & no dir . or ..*/
			f_a == EXIT_SUCCESS || r_entry->d_name[0] != '.') /* Or opt a Or dirname */
		{
			dn = r_entry->d_name, *sz = malloc((20 + 2) * sizeof(char));	/* Memory */
			*fl = malloc((_strlen(dn) + 2) * sizeof(char));					/* Please */
			if (f_R == EXIT_SUCCESS && _isdir(dirs, dn) == S_IFDIR)	/* If -R & dir */
			{
				*ldr = malloc((_strlen(dirs) +  _strlen(dn) + 3) * sizeof(char)); /*Mem*/
				if (*ldr == NULL)
				{	_freedp(fls), _freedp(szs), _freedp(ldrs);
					return (NULL);
				}
				sprintf(*ldr, "%s%c", dn, '\0'), ldr++;
			}
			if (*fl == NULL || *sz == NULL) /* If no mem */
			{	_freedp(fls), _freedp(szs), _freedp(ldrs);
				return (NULL);
			}
			sprintf(*fl, "%s%c", dn, '\0');
			if (f_t == EXIT_SUCCESS)	/* If -t was set */
				sprintf(*sz, "%0*ld%c", 20, _gtime(dirs, dn), '\0');
			else						/* If not -t */
				sprintf(*sz, "%0*d%c", 20, (int)_gsize(dirs, dn), '\0');
			fl++, sz++;	/* Move pointers to store next file name and size */
		}				 /* Close dir & Sort file list & Mem for return */
	closedir(dir), _sfd(szs, fls, NOCASE), ret = malloc(2 * sizeof(char *));
	if (ret == NULL)
	{	_freedp(fls), _freedp(szs), _freedp(ldrs);
		return (NULL);
	}
	_freedp(szs), *ret = fls, *(ret + 1) = ldrs; /* Release mem & return */
	return (ret);
}
