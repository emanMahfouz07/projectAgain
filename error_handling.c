#include "shell.h"

/**
 * convert_error_integer - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int convert_error_integer(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error_message - prints an error message
 * @info: the parameter & return info struct
 * @str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error_message(infom_t *info, char *str)
{
	_P_error_string(info->file_Name);
	_P_error_string(": ");
	print_directory(info->linesCount, STDERR_FILENO);
	_P_error_string(": ");
	_P_error_string(info->argvm[0]);
	_P_error_string(": ");
	_P_error_string(str);
}

/**
 * print_directory - function prints a decimal (integer) number (base 10)
 * @in: the input
 * @dict: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_directory(int in, int dict)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _ab_, current;

	if (dict == STDERR_FILENO)
		__putchar = _errputchar;
	if (in < 0)
	{
		_ab_ = -in;
		__putchar('-');
		count++;
	}
	else
		_ab_ = in;
	current = _ab_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_ab_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_integer_to_string - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_integer_to_string(long int num, int base, int flags)
{
	static char *arrays;
	static char buffe[50];
	char si = 0;
	char *pt;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		si = '-';

	}
	arrays = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &buffe[49];
	*pt = '\0';

	do	{
		*--pt = arrays[n % base];
		n /= base;
	} while (n != 0);

	if (si)
		*--pt = si;
	return (pt);
}

/**
 * remove_comments_from_input - func replaces first inst of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments_from_input(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
