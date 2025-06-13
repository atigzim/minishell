#include "minishell.h"


void search_ex(char *command, char **env)
{
    int pid;
    char *str = getenv("PATH");
    int len = ft_strlen(str);
    char **paths = ft_split(str, ':');
    int is_command = (strchr(command, '/') == NULL) && (strchr(command, '$') == NULL);
    int i = 0;
    if(is_command)
    {
        check_and_run(paths, command, env);
    }
    else
    {
        pid = fork();
        char **args = ft_split(command, ' ');
        if(pid == 0)
        {
            if(!access(command, X_OK))
            {
                execve(command, args, env);
                perror("error execve");
            }
            else
                perror("file error");
            exit(1);
        }
        else
            waitpid(pid, NULL, 0);
    }
}