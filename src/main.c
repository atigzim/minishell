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
char *give_me_a_path(t_node *com, char **envp)
{
	int j;
	int i;
	char **path;

	i = 0;
	j = 0;
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
		path[i] = ft_strjoin(path[i], com->cmd[0]);
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
void ex_com(t_node *com, char **envp)
{
	int i;
	int j;
	int id;
	char *path;

	i = 0;
	j = 0;

	path = give_me_a_path(com, envp);
	id = fork();
	if ( id == 0)
	{
		if (execve(path, com->cmd, envp) == -1)
			perror("zsh: command not found");
		exit(1);
	}
	wait(NULL);
}
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
			// If there is a previous pipe, read from it
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0); // stdin from previous pipe
				close(prev_fd);
			}
			// If this is not the last command, write to pipe
			if (i < count - 1)
			{
				close(fd[0]);      // Close read end
				dup2(fd[1], 1);    // stdout to write end
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
				close(prev_fd); // close old read-end

			if (i < count - 1)
			{
				close(fd[1]);    // close write-end in parent
				prev_fd = fd[0]; // store read-end for next child
			}
			com = com->next;
			i++;
		}
	}

	// Wait for all child processes
	while (i-- > 0)
		wait(NULL);
}

// void ex_pipe(t_node *com, int count, char **envp)
// {
// 	int i = 0;
// 	int fd[2];
// 	int fd_sev = -1;
// 	pid_t id;
// 	char *path;

// 	while (com && i < count )
// 	{
// 		if (i < count - 1)
// 			pipe(fd);
// 		id = fork();
// 		if (id == 0)
// 		{
// 			if(fd_sev != -1)
// 			{
// 				close(fd[0]);
// 				dup2(fd[1], 0);
// 				close (fd[1]);
// 			}
// 			path = give_me_a_path(com, envp);
// 			if (execve(path, com->cmd, envp ) == -1)
// 				perror ("command not found");
// 		}
// 		else
// 		{
//             if (fd_sev != -1)
// 				close(fd_sev);
// 			if(i < count - 1)
// 			{
// 				close(fd[1]);
// 				fd_sev = fd[0];
// 				close (fd[0]);
// 			}
// 			i++;
// 			com = com->next; 
          
// 		}
//         while (i--)
//         {
//            wait(NULL);
//         }
        
          	
				
// 	}
	
// }
char *qoute_remov(char *line)
{
    char *new_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
    char q;
    int i = 0;
    int l = 0;

    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '\"')
        {
            q = line[i++];
            while (line[i] && line[i] != q)
                new_line[l++] = line[i++];
            if (line[i])
                i++;
        }
        else
            new_line[l++] = line[i++];
    }
    new_line[l] = '\0';
    return (new_line);
}

int main(int ac, char **av, char **envp)
{
    (void)av;
    (void)ac;
    (void)envp;
    char *line;
    char **s_line = NULL;
    while (1)
    {
        t_node *test = NULL;
        line = readline("\033[32m Dash@Ameed$ \033[0m");
        if (!line)
        return 0;
        add_history(line);
        int i = 0;
        if (d_quote(line, 0, 0, 0) == 0 || !check_pipe(line))
            printf(" Dash@Ameed: syntax error near unexpected\n");
        else
        {
            char *plus = expand_line(line, 0, ft_strdup(""));
            s_line = ft_split(plus, '|');
            while (s_line[i])
            {
                if (!lexer(&test, s_line[i], NULL))
                {
                    free(test);
                    test = NULL;
                    break;
                }
                i++;
            }
        } 

        t_node *test_test = test;
        int f = 0;
        while (test_test)
        {
            f++;
            test_test = test_test->next;
        }
        if (f == 1)
            ex_com(test, envp);
        else if (f > 1)
            ex_pipe(test, f, envp);
        // while (test_test)
        // {
        //     t_redi *lol = test_test->file;
        //     i = 0;
        //     while (test_test->cmd[i])
        //     {
        //         printf("cmd[ %s ]   ", test_test->cmd[i]);
        //         i++;
        //     }
        //     printf("\n");
        //     while (lol)
        //     {
        //         printf("file_num[ %s ] --> ", lol->file_num);
        //         if (lol->type == 0)
        //             printf("type_file [ FILE_IN ]\n");
        //         else if (lol->type == 1)
        //             printf("type_file [ FILE_OUT \n]");
        //         else if (lol->type == 2)
        //             printf("type_file [ FILE_APPEND ]\n");
        //         else
        //             printf("type_file [ FILE_HEREDOC ]\n");
        //         lol = lol->next;
        //     }
        //     printf("-------------------------------------------\n");
        //     test_test = test_test->next;
        // }
    }
    clear_history();
}