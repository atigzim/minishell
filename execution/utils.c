#include "../minishell.h"

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
