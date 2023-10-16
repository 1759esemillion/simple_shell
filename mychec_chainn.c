#include "shell.h"

/**
 * _chain - checks current char
 * @info: a struct
 * @buf: the buffer
 * @p: the address
 *
 * Return: 1 otherwise 0
 */
int _chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buffer_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buffer_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * chain_check - function to check from previous status
 * @info: parameter
 * @buf: the buffer
 * @p: the address
 * @i: start
 * @len: the buffer length
 * Return: void
 */
void chain_check(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buffer_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buffer_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
<<<<<<< HEAD
 * rep_alias - Will replace alias
 * @info: parameter
=======
 * replace_alias - function to replace alias
 * @info: the parameter
>>>>>>> b8b4ffc0cb518be41b918e41f0566928bcf60e54
 * Return: 1 if replaced otherwise 0
 */
int rep_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = _snode(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
<<<<<<< HEAD
 * rep_var - Will replace variables
 * @info: parameter
=======
 * replace_var - function to replace variables
 * @info: the parameter
>>>>>>> b8b4ffc0cb518be41b918e41f0566928bcf60e54
 * Return: 1 if replaced otherwise 0
 */
int rep_var(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			rep_str(&(info->argv[i]),
				_strdup(conv_num(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			rep_str(&(info->argv[i]),
				_strdup(conv_num(getpid(), 10, 0)));
			continue;
		}
		node = _snode(info->env, &info->argv[i][1], '=');
		if (node)
		{
			rep_str(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		rep_str(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - function to replace string
 * @old: the address of previous str
 * @new: the new string
 * Return: 1 if replaced otherwise 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
