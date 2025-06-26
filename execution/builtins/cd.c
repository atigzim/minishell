#include "../../minishell.h"

int	count_args(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void cd_execution(t_min *com)
{
	int i;

	i = count_args(com->cmds);
	if(i > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return;
	}
	if(i == 1)
	{
		write(2, "cd: please provide a relative or absolute path\n", 48);
		return ;
	}
	// if(!com->cmds[1])
	// {
	// 	if (chdir("/home") == -1)
	// 		perror("cd");
	// 	return ; 
	// }
    if (chdir(com->cmds[1]) == -1)
        perror("cd");
}