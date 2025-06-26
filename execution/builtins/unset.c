#include "../../minishell.h"

void unset(t_min *com)
{
    t_env *unset;
    t_env *tmp;
    t_env *tmp2;
    int j;

    j = 1;
    tmp2 = NULL;
    while(com->cmds[j])
    {
        unset = envir()->env;
        tmp = unset;
        while(tmp)
        {
            if (ft_strcmp(com->cmds[j], tmp->key) == 0)
            {
                if (tmp2)
                    tmp2->next = tmp->next;
                else
                    envir()->env = (unset)->next;
                free(tmp->key);
                free(tmp->value);
                free(tmp);
                break;
            }
            tmp2 = tmp;
            tmp = tmp->next;
        }
        j++;
    }
}
