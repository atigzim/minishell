
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*src1;
	unsigned char	*src2;
	size_t			i;

	i = 0;
	src1 = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (src1[i] == src2[i] && src1[i] && src2[i] && i < n)
		i++;
	if (i == n)
	{
		return (0);
	}
	return (src1[i] - src2[i]);
}
