#include "../minishell.h"

char	*ft_strdup_ga(const char *s)
{
	char	*d;
	size_t	i;

	if(!s)
		return (NULL);
	i = 0;
	d = (char *)ft_malloc(sizeof(char) * ft_strlen((char *)s) + 1);
	if (!d)
		return (NULL);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}