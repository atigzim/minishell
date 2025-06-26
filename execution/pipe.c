#include "../minishell.h"

int line_path(char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;

	while(src[i])
	{
		if (src[i] == ':')
			j++;
		i++;
	}
	return (j);
}

char *give_me_a_path(t_min *com, char **envp)
{
	int j;
	int i;
	char **path;

	i = 0;
	j = 0;
    
    if(!envp[0])
        return(NULL);
	while(envp[i])
	{
		if(ft_strncmp(envp[i],"PATH=", 5) == 0)
			break;
		i++;
	}
	j = line_path(envp[i]);
	path = malloc(sizeof(char *) * j + 1);
	path = ft_split(envp[i], ':');
	i = 0;
	while(path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], com->cmds[0]);
		i++;
	}
	i = 0;
	while(path[i])
	{
		if(access(path[i], F_OK) == 0)
			break;
		i++;
	}
	return (path[i]);
}

void ex_pipe(t_min *com, char **envp)
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
            if(com->type && com->type[0] == BUILTIN)
            {
                builtins(com);
                exit(0);
            }
            else
            {
                if (ft_strchr(com->cmds[0], '/'))
                    path = com->cmds[0]; 
                else
                    path = give_me_a_path(com, envp);
                execve(path, com->cmds, envp);
                perror("execve");
                exit(1);
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
    // while (wait(NULL) > 0)
    //     ;
}