#include "shell.h"

/**
 * get_hist_file_path - gets the hist file
 * @info: parameter struct
 *
 * Return: allocated string containg hist file
 */

char *get_hist_file_path(infom_t *info)
{
	char *buf, *dir;

	dir = get_env_variable(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_getstrlen(dir) + _getstrlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_hist_to_file - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_hist_to_file(infom_t *info)
{
	ssize_t fd;
	char *filename = get_hist_file_path(info);
	list_t *nodes = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (nodes = info->hist; nodes; nodes = nodes->next_index)
	{
		_putsfdict(nodes->str, fd);
		_putfdict('\n', fd);
	}
	_putfdict(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist_from_file - reads hist from file
 * @info: the parameter struct
 *
 * Return: hist_num_counts on success, 0 otherwise
 */
int read_hist_from_file(infom_t *info)
{
	int i, last = 0, linecou = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hist_file_path(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			create_hist_list(info, buf + last, linecou++);
			last = i + 1;
		}
	if (last != i)
		create_hist_list(info, buf + last, linecou++);
	free(buf);
	info->hist_num_counts = linecou;
	while (info->hist_num_counts-- >= INT_MAX)
		delete_list_node(&(info->hist), 0);
	sort_and_renum_hist(info);
	return (info->hist_num_counts);
}

/**
 * create_hist_list - adds entry to a hist linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecou: the hist linecount, hist_num_counts
 *
 * Return: Always 0
 */
int create_hist_list(infom_t *info, char *buf, int linecou)
{
	list_t *nodes = NULL;

	if (info->hist)
		nodes = info->hist;
	append_list_node(&nodes, buf, linecou);

	if (!info->hist)
		info->hist = nodes;
	return (0);
}

/**
 * sort_and_renum_hist - renumbers the hist linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new hist_num_counts
 */
int sort_and_renum_hist(infom_t *info)
{
	list_t *nodes = info->hist;
	int i = 0;

	while (nodes)
	{
		nodes->num = i++;
		nodes = nodes->next_index;
	}
	return (info->hist_num_counts = i);
}
