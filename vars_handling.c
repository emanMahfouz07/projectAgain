#include "shell.h"

/**
 * check_chain_of_commands - test if current char in buffer is a chain delim
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int check_chain_of_commands(infom_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_types = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_types = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_types = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * handle_chain_commands - checks we should continue chaining based on last_com
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void handle_chain_commands(infom_t *info,
		char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_types == CMD_AND)
	{
		if (info->last_command)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_types == CMD_OR)
	{
		if (!info->last_command)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias_with_command - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias_with_command(infom_t *info)
{
	int i;
	list_t *nodes;
	char *p;

	for (i = 0; i < 10; i++)
	{
		nodes = search_list_starts_with(info->neigb_node, info->argvm[0], '=');
		if (!nodes)
			return (0);
		free(info->argvm[0]);
		p = _find_strchr(nodes->str, '=');
		if (!p)
			return (0);
		p = _dublicate_string(p + 1);
		if (!p)
			return (0);
		info->argvm[0] = p;
	}
	return (1);
}

/**
 * replace_vars_in_input - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars_in_input(infom_t *info)
{
	int i = 0;
	list_t *nodes;

	for (i = 0; info->argvm[i]; i++)
	{
		if (info->argvm[i][0] != '$' || !info->argvm[i][1])
			continue;

		if (!_strcmp(info->argvm[i], "$?"))
		{
			replace_string_vars(&(info->argvm[i]),
				_dublicate_string(convert_integer_to_string(info->last_command, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argvm[i], "$$"))
		{
			replace_string_vars(&(info->argvm[i]),
				_dublicate_string(convert_integer_to_string(getpid(), 10, 0)));
			continue;
		}
		nodes = search_list_starts_with(info->linkedenv, &info->argvm[i][1], '=');
		if (nodes)
		{
			replace_string_vars(&(info->argvm[i]),
				_dublicate_string(_find_strchr(nodes->str, '=') + 1));
			continue;
		}
		replace_string_vars(&info->argvm[i], _dublicate_string(""));

	}
	return (0);
}

/**
 * replace_string_vars - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string_vars(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
