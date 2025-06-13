#include "../minishell.h"

bool split_store(char *str, t_token **head)
{
    char **splits = split_cmd(str);
    if (!splits)
        return false;
    int i = 0;
    t_token *new;
    t_token *last = *head;
    if (!last && splits[0])
    {
        new = lst_store(splits[0], 0);
        if (!new)
        {
            while (splits[i])
                free(splits[i++]);
            free(splits);
            return false;
        }
        *head = new;
        last = new;
        i = 1;
    }

    while (splits[i])
    {
        new = lst_store(splits[i], i);
        if (!new)
        {
            while (*head)
            {
                t_token *tmp = (*head)->next;
                free((*head)->value);
                free(*head);
                *head = tmp;
            }
            while (splits[i])
                free(splits[i++]);
            free(splits);
            return false;
        }
        last->next = new;
        last = new;
        i++;
    }
    i = 0;
    while (splits[i])
        free(splits[i++]);
    free(splits);
    return true;
}