/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: w <w@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:08:17 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/08 15:36:48 by w                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t   ex_pipe(t_node *com, char **envp)
{
    int fd[2];
    int prev_fd; 
    pid_t pid;
    char *path;

    prev_fd = -1;
    while (com)
    {
        if (com->next) 
            pipe(fd);

        pid = fork();
        if (pid == 0) 
        {
            if (prev_fd != -1) 
            {
                dup2(prev_fd, 0); 
                close(prev_fd);
            }
            if (com->next) 
            {
                close(fd[0]); 
                dup2(fd[1], 1);
                close(fd[1]);
            }
            if(com->file)
                open_readirections(com);
            if(check_builtins(com->cmd[0]) == 1)
            {
                builtins(com);
                exit(0);
            }
            else
            {
                if (ft_strchr(com->cmd[0], '/'))
                    path = com->cmd[0]; 
                else
                    path = give_me_a_path(com, envp);
                execve(path, com->cmd, envp);
                get_exit_code(com->cmd[0]);
            }
        }
        if (prev_fd != -1)
            close(prev_fd); 
        if (com->next)
        {
            close(fd[1]);      
            prev_fd = fd[0];   
        }
        com = com->next;
    }
    
    return (pid);
}