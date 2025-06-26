#include "../minishell.h"

void bultin(t_min *minishell)
{
	
		if (minishell->cmds[0] && ft_strcmp(minishell->cmds[0], "env") == 0)
			env_execution(minishell);
		else if (minishell->cmds[0] && ft_strcmp(minishell->cmds[0], "echo") == 0)
			echo(minishell);
		else if (minishell->cmds[0] && minishell->cmds[1] &&ft_strcmp(minishell->cmds[0], "export") == 0)
			export(minishell);
		else if (minishell->cmds[0] && ft_strcmp(minishell->cmds[0], "unset") == 0)
			unset(minishell);
		else if (minishell->cmds[0] && ft_strcmp(minishell->cmds[0], "cd") == 0)
			cd_execution(minishell);	
}

void ex_com(t_min *com, char **envp)
{
	int i;
	int j;
	int id;
	char *path;

	i = 0;
	j = 0;
	if(!com)
		return;
	if(!com->redir_head && com->cmds[1] && com->type[0] == BUILTIN  )
		bultin(com);
	else
	{
		
		if (ft_strchr(com->cmds[0], '/'))
			path = com->cmds[0];
		else
			path = give_me_a_path(com, envp);
	
		id = fork();
		if ( id == 0)
		{
			// if(com->head)
			// 	dup2(com->head->delimiter, 0);
			if(com->redir_head)
				open_readirections(com);
			
			if(com && com->type[0] == BUILTIN)
				builtins(com);
			else
			{
				printf("---->%s\n", path);
				printf("hahiya : %s\n", com->cmds[1]);

				if(execve(path, com->cmds, envp) == -1)
					perror(" command not found");
			} 
			
			exit(1);
		}
		wait(NULL);
	}
	
}