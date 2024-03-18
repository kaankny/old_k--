#include <stdlib.h>
#include "../include/memory.h"
#include "../include/utils.h"
#undef malloc
#undef calloc
#undef realloc
#undef free

t_memory	*g_memory = 0;

void	add_memory(void *ptr)
{
	t_memory	*new;

	new = malloc(sizeof(t_memory));
	new->ptr = ptr;
	new->next = g_memory;
	g_memory = new;
}

void	remove_memory(void *ptr)
{
	t_memory	*tmp;
	t_memory	*prev;

	tmp = g_memory;
	prev = 0;
	while (tmp)
	{
		if (tmp->ptr == ptr)
		{
			if (prev)
				prev->next = tmp->next;
			else
				g_memory = tmp->next;
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

#include <stdio.h>

void	free_memory(void)
{
	t_memory	*tmp;

	while (g_memory)
	{
		tmp = g_memory;
		g_memory = g_memory->next;
		free(tmp->ptr);
		free(tmp);
	}
}

void	*_malloc(uint32 size)
{
	void	*ptr;
	ptr = malloc(size);
	if (!ptr)
	{
		start_print_error();
		printf("Memory allocation failed");
		end_print_error();
		free_memory();
		exit(1);
	}
	add_memory(ptr);
	return (ptr);
}

void	*_calloc(uint32 count, uint32 size)
{
	void	*ptr;
	ptr = calloc(count, size);
	if (!ptr)
	{
		start_print_error();
		printf("Memory allocation failed");
		end_print_error();
		free_memory();
		exit(1);
	}
	add_memory(ptr);
	return (ptr);
}

void	*_realloc(void *ptr, uint32 size)
{
	void	*new_ptr;
	new_ptr = realloc(ptr, size);
	if (!new_ptr)
	{
		start_print_error();
		printf("Memory allocation failed");
		end_print_error();
		free_memory();
		exit(1);
	}
	remove_memory(ptr);
	add_memory(new_ptr);
	return (new_ptr);
}

void	_free(void *ptr)
{
	remove_memory(ptr);
}
