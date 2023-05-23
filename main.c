#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	infom_t infom[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_P_error_string(av[0]);
				_P_error_string(": 0: Can't open ");
				_P_error_string(av[1]);
				_errputchar('\n');
				_errputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infom->read_dict = fd;
	}
	add_env_variables(infom);
	read_hist_from_file(infom);
	hsh(infom, av);
	return (EXIT_SUCCESS);
}
