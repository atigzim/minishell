
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*buff;
	int		len;
	int		i;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen(s) + 1;
	buff = malloc(len);
	if (!buff)
		return (NULL);
	while (s[i])
	{
		buff[i] = (f)(i, s[i]);
		i++;
	}
	buff[i] = '\0';
	return (buff);
}
