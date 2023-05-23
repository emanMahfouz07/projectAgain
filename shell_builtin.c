#include "shell.h"

/**
 * quit_shell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int quit_shell(infom_t *info)
{
	int excheck;

	if (info->argvm[1])  /* If there is an exit arguement */
	{
		excheck = convert_error_integer(info->argvm[1]);
		if (excheck == -1)
		{
			info->last_command = 2;
			print_error_message(info, "Illegal number: ");
			_P_error_string(info->argvm[1]);
			 _errputchar('\n');
			return (1);
		}
		info->errors = convert_error_integer(info->argvm[1]);
		return (-2);
	}
	info->errors = -1;
	return (-2);
}

/**
 * change_directory - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int change_directory(infom_t *info)
{
	char *s, *di, buf[1024];
	int chdir_re;

	s = getcwd(buf, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argvm[1])
	{
		di = get_env_variable(info, "HOME=");
		if (!di)
			chdir_re = /* TODO: what should this be? */
				chdir((di = get_env_variable(info, "PWD=")) ? di : "/");
		else
			chdir_re = chdir(di);
	}
	else if (_strcmp(info->argvm[1], "-") == 0)
	{
		if (!get_env_variable(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env_variable(info, "OLDPWD=")), _putchar('\n');
		chdir_re = /* TODO: what should this be? */
			chdir((di = get_env_variable(info, "OLDPWD=")) ? di : "/");
	}
	else
		chdir_re = chdir(info->argvm[1]);
	if (chdir_re == -1)
	{
		print_error_message(info, "can't cd to ");
		_P_error_string(info->argvm[1]), _errputchar('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env_variable(info, "PWD="));
		set_env(info, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * provide_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int provide_help(infom_t *info)
{
	char **argarr;

	argarr = info->argvm;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argarr); /* temp att_unused workaround */
	return (0);
}
