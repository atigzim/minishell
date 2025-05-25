#include "../minishell.h"

void ex_com(t_node *com, char **envp)
{
	int i;
	int j;
	int id;
	char *path;

	i = 0;
	j = 0;

	path = give_me_a_path(com, envp);
	id = fork();
	if ( id == 0)
	{
		if (execve(path, com->cmd, envp) == -1)
			perror("zsh: command not found");
		exit(1);
	}
	wait(NULL);
}

void cd_execution(t_node *com)
{	
    if(!com->cmd[1])
	{
		if (chdir("/home") == -1)
        	perror("cd");
		return ;
	}
    if (chdir(com->cmd[1]) == -1)
        perror("cd");
}
