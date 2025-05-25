#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL)
		return (-1);
	if (s2 == NULL)
		return (1);
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int line_path(char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;

	while(src[i])
	{
		if (src[i] == ':')
			j++;
		i++;
	}
	return (j);
}
char *give_me_a_path(t_node *com, char **envp)
{
	int j;
	int i;
	char **path;

	i = 0;
	j = 0;
	while(envp[i])
	{
		if(ft_strncmp(envp[i],"PATH=", 5) == 0)
			break;
		i++;
	}
	j = line_path(envp[i]);
	path = malloc(sizeof(char *) * j + 1);
	path = ft_split(envp[i], ':');
	i = 0;
	while(path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], com->cmd[0]);
		i++;
	}
	i = 0;
	while(path[i])
	{
		if(access(path[i], F_OK) == 0)
			break;
		i++;
	}
	return (path[i]);
}
