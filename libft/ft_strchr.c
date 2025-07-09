
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;


	if (!s || !s[0])
	{
		return NULL;
	}
	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
	}
	if ((unsigned char)c == 0)
		return (ptr);
	return (NULL);
}
