/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:08:12 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/09 15:39:09 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_builtins(char *s)
{
	if(!s)
			return (0);
	if (ft_strcmp(s, "env") == 0)
		return (1);
	else if (ft_strcmp(s, "pwd") == 0)
		return (1);
	else if (ft_strcmp(s, "export") == 0)
		return (1);
	else if (ft_strcmp(s, "cd") == 0)
		return (1);
	else if (ft_strcmp(s, "unset") == 0)
		return (1);
	else if (ft_strcmp(s, "echo") == 0)
		return (1);
	else if (ft_strcmp(s, "exit") == 0)
		return (1);
	return (0);
}

void builtins(t_node *minishell)
{
	if(!minishell)
		return ;
		if (minishell->cmd[0] && ft_strcmp(minishell->cmd[0], "env") == 0)
			env_execution(minishell);
		else if (minishell->cmd[0] && ft_strcmp(minishell->cmd[0], "echo") == 0)
			echo(minishell);
		else if (minishell->cmd[0] && ft_strcmp(minishell->cmd[0], "export") == 0)
			export(minishell);
		else if (minishell->cmd[0] && ft_strcmp(minishell->cmd[0], "unset") == 0)
			unset(minishell, 1, NULL);
		else if (minishell->cmd[0] && ft_strcmp(minishell->cmd[0], "pwd") == 0)
			pwd_execution(minishell);
		else if (minishell->cmd[0] && ft_strcmp(minishell->cmd[0], "cd") == 0)
			cd_execution(minishell);
	exit_code = 0;
}
void ex_heredoc(t_node *minishell)
{
	t_node *tmp;
	t_redi *read;
	char *temp;

	tmp = minishell;
	while (tmp)
	{
		read = tmp->file;
		while (read)
		{
			if (read->type == 3)
				minishell->file->heredoc_file = heredoc(tmp, read, envir()->env);
			read = read->next;
		}
		tmp = tmp->next;
	}
}

void execution(t_node *minishell)
{
	char **env;
	t_node *tpm;
	pid_t	pid; 
	t_redi *read;
	int status;
	
	if(!minishell  )
		return(free_garbage());
	env = list_arr_env(envir()->env);
	pid = -1;
	if(!env)
		return;
	tpm = minishell;
	while(tpm)
	{
		read = tpm->file;
		while (read)
		{
			if(read->type == 3)
				ex_heredoc(tpm);
			read = read->next;
		}
		tpm = tpm->next;
	}
	if (minishell && !minishell->next)
	{
		pid = ex_com(minishell, env);
		ex_signal();
	}
	else if(minishell && minishell->next)
	{
		pid = ex_pipe(minishell, env);
		
	}
	if (pid != -1)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
		}
	}
	while (wait(NULL) > 0)
        ;
	free_garbage();
	signal_ex();
	
}
