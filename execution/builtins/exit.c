#include "../../minishell.h"

void exit_ex(t_node *minishell)
{
	if(!minishell)
		return;
	if(minishell->cmd[1])
	{
		if (ft_isalpha(minishell->cmd[1][0]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			exit(255);
		}
		if(count_args(minishell->cmd) > 2 )
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	else
	{
		// free_env();
		// free_garbage();
		exit(exit_code);
	}
}
