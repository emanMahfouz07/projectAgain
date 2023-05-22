#include "shell.h"

/**
 * add_list_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_list_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _dublicate_string(str);
		if (!new_head->str)
		{
			ffree(new_head);
			return (NULL);
		}
	}
	new_head->next_index = *head;
	*head = new_head;
	return (new_head);
}

/**
 * append_list_node - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *append_list_node(list_t **head, const char *str, int num)
{
	list_t *new_node, *nodes;

	if (!head)
		return (NULL);

	nodes = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _dublicate_string(str);
		if (!new_node->str)
		{
			ffree(new_node);
			return (NULL);
		}
	}
	if (nodes)
	{
		while (nodes->next_index)
			nodes = nodes->next_index;
		nodes->next_index = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_string - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_string(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next_index;
		i++;
	}
	return (i);
}

/**
 * delete_list_node - deletes node at given index
 * @head: address of pointer to first node
 * @ind: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_list_node(list_t **head, unsigned int ind)
{
	list_t *nodes, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!ind)
	{
		nodes = *head;
		*head = (*head)->next_index;
		ffree(nodes->str);
		ffree(nodes);
		return (1);
	}
	nodes = *head;
	while (nodes)
	{
		if (i == ind)
		{
			prev_node->next_index = nodes->next_index;
			ffree(nodes->str);
			ffree(nodes);
			return (1);
		}
		i++;
		prev_node = nodes;
		nodes = nodes->next_index;
	}
	return (0);
}

/**
 * free_list_memory - frees all nodes of a list
 * @headpt: address of pointer to head node
 *
 * Return: void
 */
void free_list_memory(list_t **headpt)
{
	list_t *nodes, *next_node, *head;

	if (!headpt || !*headpt)
		return;
	head = *headpt;
	nodes = head;
	while (nodes)
	{
		next_node = nodes->next_index;
		ffree(nodes->str);
		ffree(nodes);
		nodes = next_node;
	}
	*headpt = NULL;
}
