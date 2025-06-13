#include "../minishell.h"

void builtins(t_lexer *minishell)
{
	
	if(!minishell)
		return ;
	if (minishell->cmds[0] && ft_strcmp(minishell->cmds[0], "env") == 0)
		env_execution(minishell);
	else if (minishell->cmds[0] && ft_strcmp(minishell->cmds[0], "echo") == 0)
		echo(minishell);
	else if (minishell->cmds[0] && ft_strcmp(minishell->cmds[0], "export") == 0)
		export(minishell);
}			
void execution(t_lexer *minishell)
{
	if(!minishell)
		return ;
	if(minishell->next)
	{
		printf("ali\n");
	}
	else
	{
		if(minishell && minishell->type[0] == BUILTIN)
			builtins(minishell);
	}
}