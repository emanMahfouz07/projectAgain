#include "shell.h"

/**
 * clear_shell_info - initializes info_t struct
 * @info: struct address
 */
void clear_shell_info(infom_t *info)
{
	info->argm = NULL;
	info->argvm = NULL;
	info->paths = NULL;
	info->argcm = 0;
}

/**
 * set_shell_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_shell_info(infom_t *info, char **av)
{
	int i = 0;

	info->file_Name = av[0];
	if (info->argm)
	{
		info->argvm = split_string(info->argm, " \t");
		if (!info->argvm)
		{

			info->argvm = malloc(sizeof(char *) * 2);
			if (info->argvm)
			{
				info->argvm[0] = _dublicate_string(info->argm);
				info->argvm[1] = NULL;
			}
		}
		for (i = 0; info->argvm && info->argvm[i]; i++)
			;
		info->argcm = i;

		replace_alias_with_command(info);
		replace_vars_in_input(info);
	}
}

/**
 * free_shell_info - frees infom_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_shell_info(infom_t *info, int all)
{
	ffree(info->argvm);
	info->argvm = NULL;
	info->paths = NULL;
	if (all)
	{
		if (!info->cmd_buf_pointer)
			free(info->argm);
		if (info->linkedenv)
			free_list_memory(&(info->linkedenv));
		if (info->hist)
			free_list_memory(&(info->hist));
		if (info->neigb_node)
			free_list_memory(&(info->neigb_node));
		ffree(info->env);
			info->env = NULL;
		free_block((void **)info->cmd_buf_pointer);
		if (info->read_dict > 2)
			close(info->read_dict);
		_putchar(BUF_FLUSH);
	}
}
