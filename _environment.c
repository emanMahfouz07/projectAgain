#include "shell.h"

/**
 * list_env_variables - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int list_env_variables(infom_t *info)
{
	print_list_string(info->linkedenv);
	return (0);
}

/**
 * get_env_variable - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @na: env var name
 *
 * Return: the value
 */
char *get_env_variable(infom_t *info, const char *na)
{
	list_t *nodes = info->linkedenv;
	char *p;

	while (nodes)
	{
		p = starts_with(nodes->str, na);
		if (p && *p)
			return (p);
		nodes = nodes->next_index;
	}
	return (NULL);
}

/**
 * set_env_variable - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int set_env_variable(infom_t *info)
{
	if (info->argcm != 3)
	{
		_P_error_string("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(info, info->argvm[1], info->argvm[2]))
		return (0);
	return (1);
}

/**
 * unset_env_variable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int unset_env_variable(infom_t *info)
{
	int i;

	if (info->argcm == 1)
	{
		_P_error_string("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argcm; i++)
		unset_env(info, info->argvm[i]);

	return (0);
}

/**
 * add_env_variables - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int add_env_variables(infom_t *info)
{
	list_t *nodes = NULL;
	size_t i;

	for (i = 0; env[i]; i++)
		append_list_node(&nodes, env[i], 0);
	info->linkedenv = nodes;
	return (0);
}
