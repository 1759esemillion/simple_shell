#include "shell.h"

/**
 * clear_info - function to initiate info_t
 * @info: a struc
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - handle initiate info_t
 * @info: a struc
 * @av: the argvect
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->file_name = av[0];
	if (info->arg)
	{
		info->argv = _str_split(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		rep_alias(info);
		rep_var(info);
	}
}

/**
 * free_info - handles info_t
 * @info: struc
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	str_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buffer)
			free(info->arg);
		if (info->env)
			_flist(&(info->env));
		if (info->history)
			_flist(&(info->history));
		if (info->alias)
			_flist(&(info->alias));
		str_free(info->environ);
			info->environ = NULL;
		isfree((void **)info->cmd_buffer);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
