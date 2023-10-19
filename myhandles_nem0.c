#include "shell.h"

/**
 * isfreed - Will free ptr
 * @ptr: ptr address
 * Return: 1 otherwise 0.
 */
int isfreed(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
