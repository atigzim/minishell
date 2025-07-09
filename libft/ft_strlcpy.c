
#include "libft.h"

size_t	ft_strlcpy(const char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	l;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	l = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	while (s[l] != '\0')
	{
		l++;
	}
	if (dstsize != '\0')
	{
		while (s[i] != '\0' && i < dstsize - 1)
		{
			d[i] = s[i];
			i++;
		}
		d[i] = '\0';
	}
	return (l);
}
