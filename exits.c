#include "shell.h"

/**
 **_strcopy - copies a string
 *@destin: the destination string to be copied to
 *@srcu: the source string
 *@num: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strcopy(char *destin, char *srcu, int num)
{
	int index, j;
	char *s = destin;

	index = 0;
	while (srcu[index] != '\0' && index < num - 1)
	{
		destin[index] = srcu[index];
		index++;
	}
	if (index < num)
	{
		j = index;
		while (j < num)
		{
			destin[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@destin: the first string
 *@src: the second string
 *@num: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *destin, char *src, int num)
{
	int i, j;
	char *s = destin;

	i = 0;
	j = 0;
	while (destin[i] != '\0')
		i++;
	while (src[j] != '\0' && j < num)
	{
		destin[i] = src[j];
		i++;
		j++;
	}
	if (j < num)
		destin[i] = '\0';
	return (s);
}

/**
 **_find_strchr - locates a character in a string
 *@s: string to be parsed
 *@m: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_find_strchr(char *s, char m)
{
	do {
		if (*s == m)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
