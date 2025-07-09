/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:08:07 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/08 21:13:24 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void bultin(t_node *minishell)
{
	if (minishell->cmd[0] && ft_strcmp(minishell->cmd[0], "env") == 0)
		env_execution(minishell);
	else if (minishell->cmd[0] && ft_strcmp(minishell->cmd[0], "echo") == 0)
		echo(minishell);
	else if (minishell->cmd[0] && minishell->cmd[1] &&ft_strcmp(minishell->cmd[0], "export") == 0)
		export(minishell);
	else if (minishell->cmd[0] && ft_strcmp(minishell->cmd[0], "unset") == 0)
		unset(minishell, 1, NULL);
	else if (minishell->cmd[0] && ft_strcmp(minishell->cmd[0], "cd") == 0)
		cd_execution(minishell);
	else if (minishell->cmd[0] && ft_strcmp(minishell->cmd[0], "pwd") == 0)
		pwd_execution(minishell);
	
}

int line_path(char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if(!src)
		return (0);
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
	int (j), (i);
	char **path;

	i = 0;
	j = 0;
    if(!envp  || !envp[0])
        return(NULL);
	while(envp[i])
	{
		if(ft_strncmp(envp[i],"PATH=", 5) == 0)
			break;
		i++;
	}
	if (!envp[i])
		return(NULL);
	j = line_path(envp[i]);
	path = ft_malloc(sizeof(char *) * j + 1);
	path = ft_split_ga(envp[i], ':');
	i = 0;
	while(path[i])
	{
		path[i] = ft_strjoin_ga(path[i], "/");
		path[i] = ft_strjoin_ga(path[i], com->cmd[0]);
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

char  **list_arr_env(t_env *env)
{
	int i = 0;
	char **arr;
	char *key_eq;
	char *key_eq_val;

	if (!env)
		return (NULL);
	t_env *temp = env;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	arr = ft_malloc(sizeof(char *) * (i + 1));
	if (!arr)
		return (NULL);

	i = 0;
	while (env)
	{
		key_eq = ft_strjoin_ga(env->key, "=");
		key_eq_val = ft_strjoin_ga(key_eq, env->value);
		if(key_eq_val)
		{
			arr[i] = key_eq_val;
			i++;
		}
		env = env->next;
	}
	arr[i] = NULL;
	i = 0;
	return (arr);
}

void	ft_puterror(char *cmd, char *msg, int exit_code)
{
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, msg, ft_strlen(msg));
	exit(exit_code);
}

void	get_exit_code(char *cmd)
{
	struct stat	sb;

	if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
		ft_puterror(cmd, ": Is a directory\n", 126);
	if (errno == EACCES)
		ft_puterror(cmd, ": Permission denied\n", 126);
	if (ft_strchr(cmd, '/'))
		ft_puterror(cmd, ": No such file or directory\n", 127);
	else
		ft_puterror(cmd, ": command not found\n", 127);
}

void shellvl()
{
	t_env *env;
	int i = 0;
	
	env = envir()->env;
	while(env)
	{
		if(ft_strcmp(env->key , "SHLVL") == 0)
		{
			i = ft_atoi(env->value);
			i++;
			env->value = ft_itoa(i);
			break;
		}
		env = env->next;
	}
}

void child_execve(t_node *com, int flag, char *path, char **envp)
{
	signal(SIGINT, SIG_DFL);
	if (open_readirections(com) == -1)
		perror("redirection : ");
	if (flag == 1)
		exit(0);
	if(check_builtins(com->cmd[0]) == 1)
	{
		builtins(com);
		free_garbage();
		exit(exit_code);
	}
	else
	{
		execve(path, com->cmd, envp);
		free_garbage();
		free_env();
		get_exit_code(com->cmd[0]);
	}
}
pid_t	ex_com(t_node *com, char **envp)
{
	int (i), (j), (flag);
	pid_t id;
	char **arr;
	char *path;
	int status;

	i = 0;
	j = 0;
	flag = 0;
	if (com->cmd[0] && ft_strcmp(com->cmd[0], "exit") == 0)
		exit_ex(com);
	if(!com->file && com->cmd[1] && check_builtins(com->cmd[0]))
	{
		printf("dkhalt\n");
		bultin(com);
		free_garbage();
	}
	else
	{
		if (!com->cmd[0])
			flag = 1;
		else
		{
			if (ft_strchr(com->cmd[0], '/'))
				path = com->cmd[0];
			else
				path = give_me_a_path(com, envp);
		}
		
		id = fork();
		if (id == 0)
			child_execve(com, flag, path, envp);
		
	}
	return (id);
}
