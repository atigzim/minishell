#include "../minishell.h"

bool check_expansion(char *str)
{
    if(str[0] == '$' || str[0] == '"')
    {
        return true;
    }
    return false;
}

char *handle_quotes(char *str)
{
    int i = 1;
    int len = ft_strlen(str);
    char *new_str;

    if (len == 2)
    {
        new_str = malloc(1);
        new_str[0] = '\0';
        return new_str;
    }

    new_str = malloc(len - 1);
    while (i < len - 1)
    {
        new_str[i - 1] = str[i];
        i++;
    }

    new_str[i - 1] = '\0';
    free(str);
    return new_str;
}

char *expand_vr(char *str, char **variables, char **env)
{
    int i = 0;
    int d = 0;
    char *new_str = handle_quotes(str);
    char *expanded_str = NULL;
    char *var_name;
    char final_str[1024] = {0};
    char *all_str = NULL;
    while(new_str[i] != '$')
        i++;
    i++;
    int j = i;
    while(new_str[j] && new_str[j] != ' ' && new_str[j] != '\t' && new_str[j] != '"' && new_str[j] != '\'')
        j++;
    var_name = malloc(j - i + 1);
    ft_strlcpy(var_name, new_str + i, j - i + 1);
    i = 0;
    while(variables[i])
    {
        if(ft_strcmp(variables[i], var_name) == 0)
        {
            expanded_str = ft_strdup(env[i]);
            break;
        }
        i++;
    }
    if(!variables[i])
    {
        return new_str;
    }
    d = 0;
    i = 0;
    while(new_str[d] != '$')
    {
        final_str[i] = new_str[d];
        i++;
        d++;
    }
    j = ft_strlen(var_name) + 1;
    while(expanded_str[j])
    {
        final_str[i] = expanded_str[j];
        j++;
        i++;
    }
    int var_len = ft_strlen(var_name);
    int all = i;
    i = 0;
    d++;
    while(new_str[d + var_len])
    {
        final_str[all + i] = new_str[d + var_len];
        d++;
        i++;
    }
    free(new_str);
    free(var_name);
    free(expanded_str);
    all_str = ft_strdup(final_str);
    return all_str;
}

char *normal_expand(char *str, char **variables, char **env)
{
    char str_copy[1024];
    int i = 1;
    int j = 0;
    while(str[i])
    {
        str_copy[j] = str[i];
        i++;
        j++;
    }
    str_copy[j] = '\0';
    i = 0;
    char *expanded_str = NULL;
    while(variables[i])
    {
        if(ft_strcmp(variables[i], str_copy) == 0)
        {
            expanded_str = ft_strdup(env[i]);
            break;
        }
        i++;
        if(!variables[i])
        {
            return str;
        }
    }
    char *final_str = malloc(ft_strlen(expanded_str) - ft_strlen(str_copy) + 1);
    i = 0;
    while(expanded_str[i + ft_strlen(str_copy) + 1])
    {
        final_str[i] = expanded_str[i + ft_strlen(str_copy) + 1];
        i++;
    }
    final_str[i] = '\0';
    free(expanded_str);
    free(str);
    return final_str;
}

void expand_variabls(t_lexer *head, char **variables , char **env)
{
    t_lexer *tmp = head;
    int i = 0;
    while(tmp)
    {
        i = 0;
        while(tmp->cmds[i])
        {
            if(check_expansion(tmp->cmds[i]))
            {
                if(ft_strchr(tmp->cmds[i], '$'))
                {
                    if(ft_strchr(tmp->cmds[i], '"'))
                        tmp->cmds[i] = expand_vr(tmp->cmds[i], variables, env);
                    else
                        tmp->cmds[i] = normal_expand(tmp->cmds[i], variables, env);
                }
                else
                    tmp->cmds[i] = handle_quotes(tmp->cmds[i]);
            }
            else if(tmp->cmds[i][0] == '\'')
                tmp->cmds[i] = handle_quotes(tmp->cmds[i]);
            i++;
        }
        tmp = tmp->next;
    }
}