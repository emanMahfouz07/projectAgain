#include "shell.h"

/**
 * interactive_shell - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive_shell(infom_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_dict <= 2);
}

/**
 * check_if_delimiter - checks if character is a delimeter
 * @c: the char to check
 * @delimiter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int check_if_delimiter(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return (1);
	return (0);
}

/**
 *check_alpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int check_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *convert_to_integer - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int convert_to_integer(char *s)
{
	int i, si = 1, flags = 0, outputs;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flags != 2; i++)
	{
		if (s[i] == '-')
			si *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flags = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}

	if (si == -1)
		outputs = -result;
	else
		outputs = result;

	return (outputs);
}
