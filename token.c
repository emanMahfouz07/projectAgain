#include "shell.h"

/**
 * **split_string - splits a string into words. Repeated delimiters are ignored
 * @strn: the input string
 * @dd: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **split_string(char *strn, char *dd)
{
	int id, j, k, m, numwords = 0;
	char **c;

	if (strn == NULL || strn[0] == 0)
		return (NULL);
	if (!dd)
		dd = " ";
	for (id = 0; strn[id] != '\0'; id++)
		if (!check_if_delimiter(strn[id],
				dd) && (check_if_delimiter(strn[id + 1], dd) || !strn[id + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	c = malloc((1 + numwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (id = 0, j = 0; j < numwords; j++)
	{
		while (check_if_delimiter(strn[id], dd))
			id++;
		k = 0;
		while (!check_if_delimiter(strn[id + k], dd) && strn[id + k])
			k++;
		c[j] = malloc((k + 1) * sizeof(char));
		if (!c[j])
		{
			for (k = 0; k < j; k++)
				free(c[k]);
			free(c);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			c[j][m] = strn[id++];
		c[j][m] = 0;
	}
	c[j] = NULL;
	return (c);
}

/**
 * **split_string_by_space - splits a string into words
 * @strn: the input string
 * @ded: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string_by_space(char *strn, char ded)
{
	int i, j, k, m, nword = 0;
	char **s;

	if (strn == NULL || strn[0] == 0)
		return (NULL);
	for (i = 0; strn[i] != '\0'; i++)
		if ((strn[i] != ded && strn[i + 1] == ded) ||
		    (strn[i] != ded && !strn[i + 1]) || strn[i + 1] == ded)
			nword++;
	if (nword == 0)
		return (NULL);
	s = malloc((1 + nword) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nword; j++)
	{
		while (strn[i] == ded && strn[i] != ded)
			i++;
		k = 0;
		while (strn[i + k] != ded && strn[i + k] && strn[i + k] != ded)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = strn[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
