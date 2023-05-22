#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@m: the pointer to the memory area
 *@b: the byte to fill *s with
 *@num: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *m, char b, unsigned int num)
{
	unsigned int index;

	for (index = 0; index < num; index++)
		m[index] = b;
	return (m);
}

/**
 * ffree - frees a string of strings
 * @ss: string of strings
 */
void ffree(char **ss)
{
	char **c = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(c);
}

/**
 * *_reallocate - reallocates a block of memory
 * @pointer: pointer to previous malloc'ated block
 * @prev_size: byte size of previous block
 * @n_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_reallocate(void *pointer, unsigned int prev_size, unsigned int n_size)
{
	char *p;

	if (!pointer)
		return (malloc(n_size));
	if (!n_size)
		return (free(pointer), NULL);
	if (n_size == prev_size)
		return (pointer);

	p = malloc(n_size);
	if (!p)
		return (NULL);

	prev_size = prev_size < n_size ? prev_size : n_size;
	while (prev_size--)
		p[prev_size] = ((char *)pointer)[prev_size];
	free(pointer);
	return (p);
}
