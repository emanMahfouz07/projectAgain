#include "shell.h"

/**
 * get_env_variables - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_env_variables(infom_t *info)
{
	if (!info->env || info->changed_env)
	{
		info->env = list_to_strings(info->env);
		info->changed_env = 0;
	}

	return (info->env);
}

/**
 * unset_env - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int unset_env(infom_t *info, char *var)
{
	list_t *nodes = info->env;
	size_t i = 0;
	char *p;

	if (!nodes || !var)
		return (0);

	while (nodes)
	{
		p = starts_with(nodes->str, var);
		if (p && *p == '=')
		{
			info->changed_env = delete_list_node(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		nodes = nodes->delete_list_node;
		i++;
	}
	return (info->changed_env);
}

/**
 * set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int set_env(infom_t *info, char *var, char *val)
{
	char *buf = NULL;
	list_t *nodes;
	char *p;

	if (!var || !val)
		return (0);

	buf = malloc(_getstrlen(var) + _getstrlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, val);
	nodes = info->env;
	while (nodes)
	{
		p = starts_with(nodes->str, var);
		if (p && *p == '=')
		{
			ffree(nodes->str);
			nodes->str = buf;
			info->changed_env = 1;
			return (0);
		}
		nodes = nodes->delete_list_node;
	}
	append_list_node(&(info->env), buf, 0);
	ffree(buf);
	info->changed_env = 1;
	return (0);
}
