#include "shell.h"

/**
 * _getstrlen - returns the length of string
 * @c: the string whose length to check
 *
 * Return: integer length of string
 */
int _getstrlen(char *c)
{
	int index = 0;

	if (!c)
		return (0);

	while (*c++)
		index++;
	return (index);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strings.
 * @c1: the first strang
 * @c2: the second strang
 *
 * Return: negative if c1 < c2, positive if c1 > c2, zero if c1 == c2
 */
int _strcmp(char *c1, char *c2)
{
	while (*c1 && *c2)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
	}
	if (*c1 == *c2)
		return (0);
	else
		return (*c1 < *c2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystacke
 * @haystacke: string to search
 * @nedle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystacke, const char *nedle)
{
	while (*nedle)
		if (*nedle++ != *haystacke++)
			return (NULL);
	return ((char *)haystacke);
}

/**
 * _strcat - concatenates two strings
 * @destin: the destination buffer
 * @srcu: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *destin, char *srcu)
{
	char *ret = destin;

	while (*destin)
		destin++;
	while (*srcu)
		*destin++ = *srcu++;
	*destin = *srcu;
	return (ret);
}
