#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned int	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
	{
		ptr = NULL;
		return (ptr);
	}
	ft_bzero(ptr, count * size);
	return (ptr);
}
