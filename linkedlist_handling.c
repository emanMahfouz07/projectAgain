#include "shell.h"

/**
 * get_list_length - determines length of linked list
 * @h: pointer to first nodes
 *
 * Return: size of list
 */
size_t get_list_length(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next_index;
		i++;
	}
	return (i);
}

/**
 * convert_list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first nodes
 *
 * Return: array of strings
 */
char **convert_list_to_strings(list_t *head)
{
	list_t *nodes = head;
	size_t i = get_list_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; nodes; nodes = nodes->next_index, i++)
	{
		str = malloc(_getstrlen(nodes->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				ffree(strs[j]);
			ffree(strs);
			return (NULL);
		}

		str = _strcpy(str, nodes->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * display_list - prints all elements of a list_t linked list
 * @h: pointer to first nodes
 *
 * Return: size of list
 */
size_t display_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_integer_to_string(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next_index;
		i++;
	}
	return (i);
}

/**
 * search_list_starts_with - returns nodes whose string starts with prefix
 * @nodes: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match nodes or null
 */
list_t *search_list_starts_with(list_t *nodes, char *prefix, char c)
{
	char *p = NULL;

	while (nodes)
	{
		p = starts_with(nodes->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (nodes);
		nodes = nodes->next_index;
	}
	return (NULL);
}

/**
 * get_list_index - gets the index of a nodes
 * @head: pointer to list head
 * @nodes: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_list_index(list_t *head, list_t *nodes)
{
	size_t i = 0;

	while (head)
	{
		if (head == nodes)
			return (i);
		head = head->next_index;
		i++;
	}
	return (-1);
}
