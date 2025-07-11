
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	l;
	char	*strc;

	i = 0;
	l = 0;
	strc = (char *)haystack;
	if (!strc && needle && !len)
		return (NULL);
	if (needle[0] == '\0')
	{
		return (strc);
	}
	while (strc[i] != '\0' && i < len)
	{
		while (strc[i + l] != '\0' && strc[i + l] == needle[l] && (i + l) < len)
			l++;
		if (needle[l] == '\0')
			return (strc + i);
		i++;
		l = 0;
	}
	return (0);
}
