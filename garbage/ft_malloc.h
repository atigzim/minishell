
#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>

typedef struct s_garbage_collector
{
	void						*ptr;
	struct s_garbage_collector	*next;
}								t_grbg_collector;

void	*ft_malloc(size_t size);
void	free_garbage(void);
char	*ft_strdup_ga(const char *s);
char	*ft_strjoin_ga(char const *s1, char const *s2);
char	**ft_split_ga(char const *s, char c);

#endif