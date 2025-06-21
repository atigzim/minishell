#include "../minishell.h"


t_type check_type(char *str, t_token **tokens)
{
    
    if(ft_strlen(str) <= 2)
    {
        if(str[0] == '|'){
            return PIPE;
        }
        else if(str[0] == '<' && str[1] == '<')
            return HERE_DOC;
        else if(str[0] == '>' && str[1] == '>')
            return APPEND;
        else if(str[0] == '>' && str[1] != '>')
            return RED_OUT;
        else if(str[0] == '<' && str[1] != '<')
            return RED_IN;
    }
    if(check_builtin(str))
        return BUILTIN;
    if(check_cmd(str, tokens))
        return CMD;
    // printf("hhhhhhhhhhhh dkhal\n");
    if(check_file_name(str, tokens))
        return FILE_NAME;
    return ARGUMENT;
}

bool check_cmd(char *str, t_token **tokens)
{
    char *path = getenv("PATH");
    if (!path)
        return false;
    char **paths = ft_split(path, ':');
    if (!paths)
        return false;
    int i = 0;
    char *cmd_path = NULL;
    bool found = false;
    t_token *head = *tokens;

    while(head)
    {
        if (ft_strcmp((head)->value, str) == 0)
        {
            break;
        }
        head = head->next;
    }
    if(head && head->index == 0)
    {
        printf("hhhhhhhhhhhh dkhal\n"); 
        free(cmd_path);
        i = 0;
        while (paths[i])
            free(paths[i++]);
        free(paths);
        return true;
    }
    while (paths[i])
    {
        char *tmp = ft_strjoin(paths[i], "/");
        if (!tmp)
            break;
        if(cmd_path)
            free(cmd_path);
        cmd_path = ft_strjoin(tmp, str);
        free(tmp);
        if (!cmd_path)
            break;
        if (access(cmd_path, F_OK) == 0)
        {
            found = true;
            break;
        }
        i++;
    }
    free(cmd_path);
    i = 0;
    while (paths[i])
        free(paths[i++]);
    free(paths);
    return found;
}

bool check_file_name(char *str, t_token **tokens)
{
    t_token *head = *tokens;
    int index = -1;
    t_token *cur = head;
    //printf("%d\n", head->index);
    while (cur)
    {
        if (ft_strcmp(cur->value, str) == 0)
        {
            index = cur->index;
            break;
        }
        cur = cur->next;
    }
    if (!cur || index == 0)
        return false;
    cur = head;
    while (cur)
    {
        if (cur->index == index - 1)
        {
            if(cur->value[0] == '<' || cur->value[0] == '>')
                return true;
        }
        cur = cur->next;
    }
    return false;
}

