/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:06:19 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/09 15:16:23 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char    *join_args(char **args)
{
    char    *result;
    int     i;

    if (!args)
        return (NULL);
    i = 0;
    result = NULL;
    while (args[i])
    {
        result = ft_strjoin_ga(result, args[i]);
        if(args[i + 1])
            result = ft_strjoin_ga(result, "=");
        i++;
    }
    return (result);
}

void loop_env(char **envp, char **line, t_env *tmp, int i)
{
    while (envp[i])
    {
        line = ft_split_ga(envp[i], '=');
        if (!line)
        {
            i++;
            continue;
        }
        tmp->key = line[0];
        if (line[1] && line[2])
            tmp->value = join_args(&line[1]);
        else
            tmp->value = line[1];
        i++;
        if (envp[i])
        {
            tmp->next = ft_malloc(sizeof(t_env));
            if (!tmp->next)
                break;
            ft_bzero(tmp->next, sizeof(t_env));
            tmp = tmp->next;
        }
        else
            tmp->next = NULL;
    }
}
void storage_env(char **envp)
{
    int i;
    t_env *tmp;
    char **line;

    if (!envp)
    {
        envir()->env = NULL;
        return;
    }
    i = 0;
    envir()->env = ft_malloc(sizeof(t_env));
    tmp = envir()->env;
    loop_env(envp, line, tmp, i);
}

t_data *envir(void)
{
    static t_data env = {0};
    return (&env);
}

void env_execution(t_node *minishell)
{
    t_env *tmp;
    
    tmp = envir()->env;
    if(!tmp)
    {
        exit_code = 1;
        return;
    }
    if( minishell->cmd[1])
        return;
    while (tmp)
    {
        if(tmp->key)
        {
            printf("%s=", tmp->key);
            if(tmp->value)
                printf("%s\n",tmp->value);
            else
                printf("\n");
        }   
        tmp = tmp->next;
    }
    
}
