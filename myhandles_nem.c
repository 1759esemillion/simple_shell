#include "shell.h"

/**
 **setmemos - adds constant byte in memory
 *@s: a pointer
 *@b: the byte
 *@n: number of bytes
 *Return: a pointer
 */
char *setmemos(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * string_free -  frees a string
 * @pp: a string
 */
void string_free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - a function to reallocate block of memory
 * @ptr: a pointer
 * @old_size: a parameter
 * @new_size: a parameter
 * Return: a ptr
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
