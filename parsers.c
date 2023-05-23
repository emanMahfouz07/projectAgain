#include "shell.h"

/**
 * is_cmd_Valid - determines if a file is an executable
 * @infom: the info struct
 * @paths: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd_Valid(infom_t *infom, char *paths)
{
	struct stat ste;

	(void)infom;
	if (!paths || stat(paths, &ste))
		return (0);

	if (ste.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - function duplicates characters
 * @pathstring: the PATH string
 * @starTT: starting index
 * @stopIn: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_chars(char *pathstring, int starTT, int stopIn)
{
	static char buff[1024];
	int i = 0, n = 0;

	for (n = 0, i = starTT; i < stopIn; i++)
		if (pathstring[i] != ':')
			buff[n++] = pathstring[i];
	buff[n] = 0;
	return (buff);
}
/**
 * find_executable_path - finds cmd in the PATH string
 * @infom: the info struct
 * @pathstring: the PATH string
 * @command: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_executable_path(infom_t *infom, char *pathstring, char *command)
{
	int i = 0, current_pos = 0;
	char *paths;

	if (!pathstring)
		return (NULL);
	if ((_getstrlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_cmd_Valid(infom, command))
			return (command);
	}
	while (1)
	{
		if (!pathstring[i] || pathstring[i] == ':')
		{
			paths = _dublicate_string(pathstring, current_pos, i);
			if (!*paths)
				_strcat(paths, command);
			else
			{
				_strcat(paths, "/");
				_strcat(paths, command);
			}
			if (is_cmd_Valid(infom, paths))
				return (paths);
			if (!pathstring[i])
				break;
			current_pos = i;
		}
		i++;
	}
	return (NULL);
}
