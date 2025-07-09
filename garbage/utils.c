#include "../minishell.h"

static size_t	ft_count(char *s, char c)
{
	int	i;
	int	cou;

	i = 0;	
	cou = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			cou++;
		i++;
	}
	return (cou);
}

static char	*ft_cpy(char *s, char c)
{
	size_t	len;
	size_t	i;
	char	*p;

	len = 0;
	i = 0;
	while (s[len] && s[len] != c)
		len++;
	p = ft_malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static char	**fill_strings(char **p, char c, const char *s, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		while (*s && *s == c)
			s++;
		p[j] = ft_cpy((char *)s, c);
		if (!p[j])
			return (NULL);
		s += ft_strlen(p[j]);
		j++;
	}
	p[j] = NULL;
	return (p);
}

char	**ft_split_ga(char const *s, char c)
{
	size_t	i;
	char	**p;

	if (s == NULL)
		return (NULL);
	i = ft_count((char *)s, c);
	p = (char **)ft_malloc(sizeof(char *) * (i + 1));
	if (p == NULL)
		return (NULL);
	p = fill_strings(p, c, s, i);
	return (p);
}

char	*ft_strjoin_ga(char const *s1, char const *s2)
{
	char	*p;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (ft_strdup_ga(""));
	if (s1 == NULL && s2)
		return (ft_strdup_ga(s2));
	else if (s2 == NULL && s1)
		return (ft_strdup_ga(s1));
	p = (char *)ft_malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
		p[j++] = s1[i++];
	i = 0;
	while (s2[i])
		p[j++] = s2[i++];
	p[j] = '\0';
	return (p);
}
