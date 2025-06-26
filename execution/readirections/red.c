#include "../../minishell.h"

void open_readirections(t_min *com)
{
	int fd;
    int in = dup(STDIN_FILENO);
    int out = dup(STDOUT_FILENO);
    t_redir_lexer *redi = com->redir_head;

    while (redi)
    {
        if (redi->type == RED_OUT )
            fd = open(redi->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        else if (redi->type == RED_IN)
            fd = open(redi->file_name, O_RDONLY);
        else if (redi->type == APPEND)
            fd = open(redi->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
        else if (com->head->file_name)
            fd = open(com->head->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
        if ( fd == -1 )
        {
            perror("open failed");
            exit (1);
        }
        if (redi->type == RED_IN || com->head->file_name)
            dup2(fd, STDIN_FILENO);
        else
            dup2(fd, STDOUT_FILENO);
        close(fd);
        dup2(STDIN_FILENO, in);
        dup2(STDOUT_FILENO, out);
        redi = redi->next;
    }
}
