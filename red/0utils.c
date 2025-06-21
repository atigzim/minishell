#include "../minishell.h"

t_min *inti_min(t_redir_lexer *redir, t_heredoc *heredoc, t_lexer *lexer)
{
    t_min *min;
    t_type *type;
    t_min *head = NULL;
    t_min *tail = NULL;
    char **cmds = NULL;
    int i, len;

    while (redir || heredoc || lexer)
    {
        min = malloc(sizeof(t_min));
        if (!min)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return NULL;
        }
        min->cmds = lexer->cmds;
        min->redir_head = redir;
        min->head = heredoc;
        min->next = NULL;

        cmds = NULL;
        len = 0;


        // Choose which input source to use for building cmds
        if (redir && redir->arg)
        {
            // printf("%s\n", redir->file_name);
            while (redir->arg[len])
                len++;
            cmds = malloc(sizeof(char *) * (len + 2));
            cmds[0] = ft_strdup(redir->cmd);
            i = 0;
            while (i < len) {
                cmds[i + 1] = ft_strdup(redir->arg[i]);
                i++;
            }
            cmds[len + 1] = NULL;
        }
        else if (heredoc && heredoc->args)
        {
            while (heredoc->args[len])
                len++;
            cmds = malloc(sizeof(char *) * (len + 2));
            cmds[0] = ft_strdup(heredoc->cmd);
            i = 0;
            while (i < len) {
                cmds[i + 1] = ft_strdup(heredoc->args[i]);
                i++;
            }
            cmds[len + 1] = NULL;
        }
        else if ((redir && redir->cmd) || (heredoc && heredoc->cmd))
        {
            const char *cmd = NULL;
            if (redir && redir->cmd)
                cmd = redir->cmd;
            else if (heredoc && heredoc->cmd)
                cmd = heredoc->cmd;
            cmds = malloc(sizeof(char *) * 2);
            cmds[0] = ft_strdup(cmd);
            cmds[1] = NULL;
        }
        else if(lexer && lexer->cmds)
        {
           
             while (lexer->cmds[len])
                len++;
            //  printf("sssssssssssssssssssssssssss\n");
            cmds = malloc(sizeof(char *) * (len + 2));
            type = malloc(sizeof(t_type));
            // cmds[0] = ft_strdup(lexer->str);
           
            i = 0;
            while (i < len) {
                cmds[i] = ft_strdup(lexer->cmds[i]);
                
                i++;
            }
            cmds[len + 1] = NULL;
            min->type = lexer->type;
        }
        else
        {
            cmds = malloc(sizeof(char *));
            cmds[0] = NULL;
        }

        min->cmds = cmds;

        // Append to linked list
        if (!head)
            head = min;
        else
            tail->next = min;
        tail = min;

        if (redir)
            redir = redir->next;
        if (heredoc)
            heredoc = heredoc->next;
        if(lexer)
            lexer = lexer->next;
    }
    return head;
}
