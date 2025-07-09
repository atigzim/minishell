/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:06:44 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/09 15:19:03 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void free_unset(t_env *tmp)
{
    free(tmp->key);
    free(tmp->value);
    free(tmp);
}
// void unset(t_node *com, int j,  t_env *tmp2 )
// {
//     t_env *unset;
//     t_env *tmp;
    
//     while(com->cmd[j])
//     {
//         unset = envir()->env;
//         tmp = unset;
//         while(tmp)
//         {
//             if (ft_strcmp(com->cmd[j], tmp->key) == 0)
//             {
//                 if (tmp2)
//                     tmp2->next = tmp->next;
//                 else
//                     envir()->env = (unset)->next;
//                 free_unset(tmp);
//                 break;
//             }
//             tmp2 = tmp;
//             tmp = tmp->next;
//         }
//         j++;
//     }
// }

void unset(t_node *com, int j,  t_env *tmp2 )
{
    t_env *unset;
    t_env *tem;
    int flag;

    flag = 0;
    unset = envir()->env;
    tmp2 = unset;
    
    while(com->cmd[j])
    {
        while (unset)
        {
            
            tem = unset->next;
            if(ft_strcmp(unset->key, com->cmd[j]) == 0)
            {
                if(flag == 0)
                    envir()->env = tem;
                else
                    tmp2->next = tem;
                flag = 0;
                break;
            }
            tmp2 = unset;
            unset = unset->next;
            flag++;
        }
        j++;
    }
}
