#include "shell.h"

/**
 *_P_error_string - prints the input string
 * @strn: the string to be printed
 *
 * Return: Nothing
 */
void _P_error_string(char *strn)
{
	int index = 0;

	if (!strn)
		return;
	while (strn[index] != '\0')
	{
		_errputchar(strn[index]);
		index++;
	}
}

/**
 * _errputchar - writes the character m to stderr
 * @m: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _errputchar(char m)
{
	static int index;
	static char buff[WRITE_BUF_SIZE];

	if (m == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buff, index);
		index = 0;
	}
	if (m != BUF_FLUSH)
		buff[index++] = m;
	return (1);
}

/**
 * _putfdict - writes the character m to given filedict
 * @m: The character to print
 * @filedict: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfdict(char m, int filedict)
{
	static int index;
	static char buff[WRITE_BUF_SIZE];

	if (m == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(filedict, buff, index);
		i = 0;
	}
	if (m != BUF_FLUSH)
		buff[index++] = m;
	return (1);
}

/**
 *_putsfdict - prints an input string
 * @strn: the string to be printed
 * @filedict: the filedescriptor to write to
 *
 * Return: the number of chars
 */
int _putsfdict(char *strn, int filedict)
{
	int index = 0;

	if (!strn)
		return (0);
	while (*strn)
	{
		index += _putfdict(*strn++, filedict);
	}
	return (index);
}
