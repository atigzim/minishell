/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:08:01 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/07 04:55:23 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int return_fd(t_redi *redi, t_node *com)
{
    int fd;
    
    if (redi->type == 1)  
        fd = open(redi->file_num, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (redi->type == 0)  
        fd = open(redi->file_num, O_RDONLY);
    else if (redi->type == 2)  
        fd = open(redi->file_num, O_CREAT | O_WRONLY | O_APPEND, 0644);
    else if (redi->type == 3 && redi->heredoc_file)  
        fd = open(com->file->heredoc_file, O_RDONLY); 
    else
        return (-1);
    return (fd);
}

int open_readirections(t_node *com)
{
    int fd;
    t_redi *redi = com->file;

    while (redi)
    {
        fd = return_fd(redi, com);
        if (fd == -1)
        {
            perror("open failed");
            exit(1);
        }
        if (redi->type == 0 || redi->type == 3)
            dup2(fd, STDIN_FILENO);
        else
            dup2(fd, STDOUT_FILENO); 

        close(fd);
        redi = redi->next;
    }
    return (0);
}
