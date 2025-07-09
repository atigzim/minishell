/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:06:44 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/05 17:30:11 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void free_unset(t_env *tmp)
{
    free(tmp->key);
    free(tmp->value);
    free(tmp);
}
void unset(t_node *com, int j,  t_env *tmp2 )
{
    t_env *unset;
    t_env *tmp;
    
    while(com->cmd[j])
    {
        unset = envir()->env;
        tmp = unset;
        while(tmp)
        {
            if (ft_strcmp(com->cmd[j], tmp->key) == 0)
            {
                if (tmp2)
                    tmp2->next = tmp->next;
                else
                    envir()->env = (unset)->next;
                free_unset(tmp);
                break;
            }
            tmp2 = tmp;
            tmp = tmp->next;
        }
        j++;
    }
}
