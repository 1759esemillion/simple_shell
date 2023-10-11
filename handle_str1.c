#include "shell.h"

/**
 * l_length - Calculate the length of a list.
 * @h: A pointer to the list.
 * Return: The size of the list.
 */
size_t l_length(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * l_str - Return an array of strings from a list.
 * @head: A pointer to the list.
 * Return: An array of strings.
 */
char **l_str(list_t *head)
{
	list_t *node = head;
	size_t i = l_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * _plist - Display elements of a list_t linked list.
 * @h: A pointer to the list.
 * Return: The size of the list.
 */
size_t _plist(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(conv_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _snode - Return a specific node based on a prefix and character.
 * @node: A pointer to the list.
 * @prefix: The string prefix to search for.
 * @c: The character to match in the prefix (-1 for any character).
 * Return: The exact node if found, otherwise NULL.
 */

list_t *_snode(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getn_ind - Fetch the index of a node in a list.
 * @head: A pointer to the list.
 * @node: A pointer to the node to find the index of.
 * Return: The index of the node if found, otherwise -1.
 */
ssize_t getn_ind(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
