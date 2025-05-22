#include "../minishell.h"

void ex_pipe(t_node *com, int count, char **envp)
{
	int i = 0;
	int fd[2];
	int prev_fd = -1;
	pid_t pid;
	char *path;

	while (com && i < count)
	{
		if (i < count - 1 && pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0);
				close(prev_fd);
			}
			if (i < count - 1)
			{
				close(fd[0]);      
				dup2(fd[1], 1);    
				close(fd[1]);
			}
			path = give_me_a_path(com, envp);
			execve(path, com->cmd, envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd); 

			if (i < count - 1)
			{
				close(fd[1]);   
				prev_fd = fd[0]; 
			}
			com = com->next;
			i++;
		}
	}

	while (i-- > 0)
		wait(NULL);
}
