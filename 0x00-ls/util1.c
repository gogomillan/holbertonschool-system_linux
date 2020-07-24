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
