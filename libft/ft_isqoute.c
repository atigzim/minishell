
#include "libft.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	skip_quote(const char *s, int i)
{
	char	quote;

	quote = s[i++];
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}
