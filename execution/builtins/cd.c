/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:06:08 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/06 20:36:20 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void old_pwd()
{
	t_env *env;
	char *value;
	char pwd[4096];

	env = envir()->env;
	value = NULL;
	while (env)
	{
		if(ft_strcmp(env->key, "PWD") == 0)
		{
			value = ft_strdup(env->value);
			getcwd(pwd, sizeof(pwd));
			env->value = pwd;
			break;
		}
		env = env->next;
	}
	env = envir()->env;
	while (env)
	{
		if(ft_strcmp(env->key, "OLDPWD") == 0)
		{
			env->value = value;
			break;
		}
		env = env->next;
	}
}

int	count_args(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void cd_execution(t_node *com)
{
	int i;

	i = count_args(com->cmd);
	if(i > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		exit_code = 1;
		return;
	}
	if(i == 1)
	{
		write(2, "cd: please provide a relative or absolute path\n", 48);
		exit_code = 1;
		return ;
	}
    if (chdir(com->cmd[1]) == -1)
	{
		exit_code = 1;
        perror("cd");
	}
	old_pwd();
}
