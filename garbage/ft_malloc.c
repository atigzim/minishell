#include "ft_malloc.h"

t_grbg_collector	**get_gc(void)
{
	static t_grbg_collector	*gc;

	return (&gc);
}

void	track_allocation(void *ptr)
{
	t_grbg_collector	**gc;
	t_grbg_collector	*tmp;

	gc = get_gc();
	if (!*gc)
	{
		*gc = malloc(sizeof(t_grbg_collector));
		if (!*gc)
			return ;
		(*gc)->ptr = ptr;
		(*gc)->next = NULL;
	}
	else
	{
		tmp = *gc;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(t_grbg_collector));
		if (!tmp->next)
			return ;
		tmp->next->ptr = ptr;
		tmp->next->next = NULL;
	}
}

void	free_garbage(void)
{
	t_grbg_collector	**gc;
	t_grbg_collector	*tmp;

	gc = get_gc();
	while (*gc)
	{
		tmp = (*gc)->next;
		free((*gc)->ptr);
		free(*gc);
		*gc = tmp;
	}
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	track_allocation(ptr);
	return (ptr);
}