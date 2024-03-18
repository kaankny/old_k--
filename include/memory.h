#ifndef MEMORY_H
# define MEMORY_H

/*
** DEFINITIONS
*/
# define uint32					unsigned int		// Unsigned integer (32 bits)
# define malloc(size)			_malloc(size)		// Allocate memory
# define calloc(count, size)	_calloc(count, size)// Allocate and zero-initialize memory
# define realloc(ptr, size)		_realloc(ptr, size)	// Reallocate memory
# define free(ptr)				_free(ptr)			// Deallocate memory

/*
** MEMORY STRUCTURE DEFINITION (SINGLY LINKED LIST)
*/
typedef struct s_memory
{
	void			*ptr;	// Pointer to the allocated memory
	struct s_memory	*next;	// Next memory block in the list (NULL if the last memory block in the list)
}	t_memory;

/*
** GLOBAL MEMORY POINTER DECLARATION
*/
extern t_memory	*g_memory; // Pointer to the first memory block in the list

/*
** MEMORY FUNCTIONS DECLARATION
*/
void	add_memory(void *ptr);				// Add memory block to the list
void	remove_memory(void *ptr);			// Remove memory block from the list
void	free_memory(void);					// Free all memory blocks in the list
void	*_malloc(uint32 size);				// Allocate memory
void	*_calloc(uint32 count, uint32 size);// Allocate and zero-initialize memory
void	*_realloc(void *ptr, uint32 size);	// Reallocate memory
void	_free(void *ptr);					// Deallocate memory

#endif