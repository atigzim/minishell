#include "../minishell.h"


void builtins(t_min *minishell)
{
	if(!minishell)
		return ;
		if (minishell->cmds[0] && ft_strcmp(minishell->cmds[0], "env") == 0)
			env_execution(minishell);
		else if (minishell->cmds[0] && ft_strcmp(minishell->cmds[0], "echo") == 0)
			echo(minishell);
		else if (minishell->cmds[0] && ft_strcmp(minishell->cmds[0], "export") == 0)
			export(minishell);
		else if (minishell->cmds[0] && ft_strcmp(minishell->cmds[0], "unset") == 0)
			unset(minishell);
		else if (minishell->cmds[0] && ft_strcmp(minishell->cmds[0], "pwd") == 0)
			pwd_execution(minishell);
		else if (minishell->cmds[0] && ft_strcmp(minishell->cmds[0], "cd") == 0)
			cd_execution(minishell);
}
void execution(t_min *minishell, char **envp)
{
	t_heredoc *her;
	
	her = minishell->head;
    while(minishell && her )
	{
		// heredoc(her);
		heredoc(minishell);
		her = her ->next;
	}
	if(minishell && minishell->next)
	{	
		ex_pipe(minishell, envp);
	}
	else
	{
		
		ex_com(minishell, envp);
	}
	while (wait(NULL) > 0)
        ;
}