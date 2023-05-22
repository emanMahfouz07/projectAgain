#inlcude "shell.h"

/**
 * hsh - main shell loop
 * @infom: parameter and return struct info
 * @av: argument vector
 *
 * Return: 0 if success , 1 on error
 */
int hsh(infom_t *infom, char **av)
{
	ssize_t size = 0;
	int built_return = 0;

	while (size != -1 && built_return != -2)
	{
		clear_shell_info(infom);
		if (interactive_shell(infom))
			_puts("$ ");
		_errputchar(BUF_FLUSH);
		size = read_input(infom);
		if (size != -1)
		{
			set_shell_info(infom, av);
			built_return = find_builtFunc(infom);
			if (built_return == -1)
				find_cmd(infom);
		}
		else if (interactive_shell(infom))
			_putchar('\n');
		free_shell_info(infom, 0);
	}
	write_hist_to_file(infom);
	free_shell_info(infom, 1);
	if (!interactive_shell(infom) && infom->last_command)
		exit(infom->last_command);
	if (built_return == -2)
	{
		if (infom->errors == -1)
			exit(infom->last_command);
		exit(infom->errors);
	}
	return(built_return);
}
/**
 * find_builtFunc - finds a builtFunc command
 * @infom: the parameter & return info struct
 *
 * Return: -1 if builtFunc not found,
 *			0 if builtFunc executed successfully,
 *			1 if builtFunc found but not successful,
 *			-2 if builtFunc signals exit()
 */
int find_builtFunc(infom_t *infom)
{
	int i, built_in_return = -1;
	built_funcs_table builtFuntbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtFuntbl[i].type; i++)
		if (_strcmp(infom->argv[0], builtFuntbl[i].type) == 0)
		{
			infom->linesCount++;
			built_in_return = builtFuntbl[i].func(infom);
			break;
		}
	return (built_in_return);
}
/**
 * find_builtFunc - finds a command in PATH
 * @infom: the parameter & return info struct
 *
 * Return: void
 */
void find_builtFunc(infom_t *infom)
{
	pid_t chd_pid;
	chd_pid = fork();
	if (chd_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (chd_pid == 0)
	{
		if (execve(infom->paths, infom->argvm, get_env_variables(info)) == -1)
		{
			free_shell_info(infom, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(infom->last_command));
		if (WIFEXITED(infom->last_command))
		{
			infom->last_command = WEXITSTATUS(infom->last_command);
			if (infom->last_command == 126)
				print_error_message(infom, "Permission denied\n");
		}
	}
}
