/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:06:32 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/09 15:17:47 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// handli ali+=tig
int plus (char *s)
{
	int i;

    i = 0;
    while(s[i])
    {
        if(s[i] == '+')
            return (1);
        i++;
    }
    return (0);
}

char **parsing_export(char *s)
{
    char **args;
    int i;
    
    i = 0;
    if(!s)
        return (NULL);
    if (ft_isalpha(*s) == 0 && *s != '_')
    {
        printf("export: `%s': not a valid identifier\n", s);
        return (NULL);
    }
    args = ft_split_ga(s, '=');
	
    return (args);
}

int check_env_kay(char *arg)
{
    t_env *env;

    env = envir()->env;
    while(env)
    {

        if(plus(arg) == 1)
        {
            if(ft_strncmp(env->key, arg, ft_strlen(arg) - 1) == 0)
                return (1);
        }
        else
            if(ft_strcmp(env->key, arg) == 0)
                return (1);
        env = env->next;
    }
    return (0);
}

void sort_env(t_env *export)
{
    t_env *tmp;
    t_env *head;
    char *swp_key;
    char *swp_value;

    tmp = export;
    head = tmp;
    while (head && head->next)  
    {
        if (ft_strncmp(head->key, head->next->key, 1) > 0)
        {
            swp_key = head->key;
            swp_value = head->value;
            head->key = head->next->key;
            head->value = head->next->value;
            head->next->key = swp_key;
            head->next->value = swp_value;
            head = tmp; 
        }
        else
            head = head->next;
    }
    tmp = envir()->env;
    tmp = head;
}

void print_export(t_env *env)
{
    printf("%s", env->key);
    if(env->value)
        printf("=\"%s\"", env->value);
    printf("\n");
}

void export(t_node *com)
{

    static t_env *tmp;
    t_env *env;
    char **arg;
    int j;
    int k;
    static int i;

    env = envir()->env;
    j = 1;
    if (i == 0)
    {
        sort_env(env);
        i++;
    }
    if ((com)->cmd[j])
    {
        
        while ((com)->cmd[j])
        {

            if((com)->cmd[j] && (com)->cmd[j][0] != '=')
            {
                
                arg = parsing_export((com)->cmd[j]);
                    if(arg && arg[0] && plus(arg[0]) == 0)
                    {
                        if(check_env_kay(arg[0]) == 0)
                        {
                            tmp = ft_malloc(sizeof(t_env));
                            tmp->key = arg[0];
                            tmp->value = arg[1];
                            tmp->next = NULL;
							
                            while (env->next)
                                env= env->next;
                            env->next = tmp;
                        }
                        else
                        {
                            
                            env = envir()->env;
                            while(env)
                            {
                                if(ft_strcmp(env->key, arg[0])== 0)
                                {
                                    if(arg[1])
                                        env->value = arg[1];
                                    break;
                                }
                                env = env->next;
                            }
                            
                        }
                    }
	                else if (arg && arg[0] && plus(arg[0]) == 1)
                    {
                        
                        while(env)
                        {
                            k = 0;
                            if(ft_strncmp(env->key, arg[0], ft_strlen(env->key)) == 0)
                            {
                                env->value = ft_strjoin(env->value, arg[1]);
                                k = 1;
                                break;
                            }
                            env = env->next;
                        }
                        if(k != 1)
                        {
                            env = envir()->env;
                            tmp = ft_malloc(sizeof(t_env));
                            tmp->key = arg[0];
                            tmp->key[ft_strlen(tmp->key) - 1] = '\0';
                            tmp->value = arg[1];
                            tmp->next = NULL;
                            while (env->next)
                                env = env->next;
                            env->next = tmp;
                        }
                    }
                    
            }
            else
            {
                printf("minishell: export: `%s': not a valid identifier\n", com->cmd[j]);
                exit_code = 1;
            }
               
            j++;
        }
    }
    else
    {
        
        while(env)
        {
            print_export(env);
            env = env->next;
        }
    }
}
