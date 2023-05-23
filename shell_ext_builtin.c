#include "shell.h"

/**
 * check_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int check_history(infom_t *info)
{
	display_list(info->hist);
	return (0);
}

/**
 * unalias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unalias(infom_t *info, char *str)
{
	char *p, c;
	int re;

	p = _find_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	re = delete_list_node(&(info->neigb_node),
		get_list_index(info->neigb_node,
			search_list_starts_with(info->neigb_node, str, -1)));
	*p = c;
	return (re);
}

/**
 * sealias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int sealias(infom_t *info, char *str)
{
	char *p;

	p = _find_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unalias(info, str));

	unalias(info, str);
	return (append_list_node(&(info->neigb_node), str, 0) == NULL);
}

/**
 * pralias - prints an alias string
 * @nodes: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int pralias(list_t *nodes)
{
	char *p = NULL, *a = NULL;

	if (nodes)
	{
		p = _find_strchr(nodes->str, '=');
		for (a = nodes->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * check_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int check_alias(infom_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *nodes = NULL;

	if (info->argcm == 1)
	{
		nodes = info->neigb_node;
		while (nodes)
		{
			pralias(nodes);
			nodes = nodes->next_index;
		}
		return (0);
	}
	for (i = 1; info->argvm[i]; i++)
	{
		p = _find_strchr(info->argvm[i], '=');
		if (p)
			sealias(info, info->argvm[i]);
		else
			pralias(search_list_starts_with(info->neigb_node, info->argvm[i], '='));
	}

	return (0);
}
