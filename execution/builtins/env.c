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
        result = ft_strjoin(result, args[i]);
        if(args[i + 1])
            result = ft_strjoin(result, "=");
        i++;
    }
    return (result);
}

void storage_env(char **envp)
{
    int i;
    t_env *tmp;
    char **line;

    if (!envp)
        return;

    i = 0;
    envir()->env = malloc(sizeof(t_env));
    tmp = envir()->env;
    while (envp[i])
    {
        line = ft_split(envp[i], '=');
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
            tmp->next = malloc(sizeof(t_env));
            if (!tmp->next)
                break;
            ft_bzero(tmp->next, sizeof(t_env));
            tmp = tmp->next;
        }
        else
            tmp->next = NULL;
    }
}

t_data *envir(void)
{
    static t_data env = {0};

    return (&env);
}

void env_execution(t_min *minishell)
{
    
    t_env *tmp;
    
    tmp = envir()->env;
    if(!tmp)
        return;
    if( minishell->cmds[1])
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