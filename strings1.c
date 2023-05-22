#include "shell.h"

/**
 * _strcpy - copies a string
 * @destin: the destination
 * @srcu: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *destin, char *srcu)
{
	int index = 0;

	if (destin == srcu || srcu == 0)
		return (destin);
	while (srcu[index])
	{
		destin[index] = srcu[index];
		index++;
	}
	destin[index] = 0;
	return (destin);
}

/**
 * _dublicate_string - duplicates a string
 * @strn: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_dublicate_string(const char *strn)
{
	int leng = 0;
	char *ret;

	if (strn == NULL)
		return (NULL);
	while (*strn++)
		leng++;
	ret = malloc(sizeof(char) * (leng + 1));
	if (!ret)
		return (NULL);
	for (leng++; leng--;)
		ret[leng] = *--strn;
	return (ret);
}

/**
 *_puts - prints an input string
 *@strn: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *strn)
{
	int index = 0;

	if (!strn)
		return;
	while (strn[index] != '\0')
	{
		_putchar(strn[index]);
		index++;
	}
}

/**
 * _putchar - writes the character m to stdout
 * @m: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char m)
{
	static int index;
	static char buff[WRITE_BUF_SIZE];

	if (m == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buff, index);
		index = 0;
	}
	if (m != BUF_FLUSH)
		buff[index++] = m;
	return (1);
}
