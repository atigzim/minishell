/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:07:49 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/07 23:53:52 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *heredoc(t_node *min, t_redi *redi,t_env *env)
{
    int flag;
    flag = 0;
    int fd;
    int id;
    char *gel;

    fd = open(".file_tmp", O_CREAT | O_TRUNC | O_WRONLY, 0777);
    if(fd < 0)
        return (NULL);
    id = fork();
    if (id == 0)
    {
        while (1)
        {
            gel = readline("> ");
            
            if (!gel || ft_strcmp(redi->file_num, gel) == 0)
            {
                
                free(gel);
                break;
            }
            // if(flag == 0)
            // {
            //     gel = ultimate_expand(gel, min->vars, env);
            // }
            write(fd, gel, ft_strlen(gel));
            write(fd, "\n", 1);
            free(gel);
        }
        close(fd);
        exit(0);
    }
    while (wait(NULL) > 0)
        ;
    close(fd);
    // min->file->heredoc_file = ft_strdup_ga(".file_tmp");
    return (ft_strdup_ga(".file_tmp"));
}


