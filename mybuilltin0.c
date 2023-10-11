#include "shell.h"

/**
 * copy_histories - shows history list
 * @info: a struct
 *  Return: Always 0
 */
int copy_histories(info_t *info)
{
	_plist(info->history);
	return (0);
}

/**
 * unsett_alias - converts alias to string
 * @info: struct
 * @str: the string
 * Return: 0 successful otherwise 1
 */
int unsett_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = d_ind(&(info->alias),
		getn_ind(info->alias, _snode(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * sett_alias - sets alias
 * @info: a struct
 * @str: string
 * Return: 0 if successful otherwise 1
 */
int sett_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsett_alias(info, str));

	unsett_alias(info, str);
	return (end_anode(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - print alias string
 * @node: a node
 * Return: 0 if successfull otherwise 1
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * copy_alias - worksas  builtin alias
 * @info: a structure
 *  Return: 0
 */
int copy_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			sett_alias(info, info->argv[i]);
		else
			print_alias(_snode(info->alias, info->argv[i], '='));
	}

	return (0);
}

