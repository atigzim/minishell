#include "libft.h"

int	ft_atoi(const char *src)
{
	int					i;
	int					s;
	unsigned long int	r;

	i = 0;
	s = 1;
	r = 0;
	while (src[i] == 32 || (src[i] >= 9 && src[i] <= 13))
		i++;
	if (src[i] == '-' || src[i] == '+')
	{
		if (src[i] == '-')
			s *= -1;
		i++;
	}
	while (src[i] >= 48 && src[i] <= 57)
	{
		r = (r * 10) + (src[i] - '0');
		if (r > 9223372036854775807 && s == 1)
			return (-1);
		if (r > 9223372036854775807 && s == -1)
			return (0);
		i++;
	}
	return (r * s);
}
