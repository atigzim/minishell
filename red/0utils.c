#include "../minishell.h"

t_min *inti_min(t_redir_lexer *redir, t_heredoc *heredoc, t_lexer *lexer)
{
    t_min *head = NULL;
    t_min *tail = NULL;

    while (redir || heredoc || lexer)
    {
        t_min *min = malloc(sizeof(t_min));
        if (!min)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return NULL;
        }

        min->head = heredoc;
        min->redir_head = redir;
        min->type = NULL;
        min->cmds = NULL;
        min->next = NULL;

        char **cmds = NULL;
        int len = 0, i = 0;

        // Determine cmds array and len
        if (redir && redir->cmd && redir->arg)
        {
            while (redir->arg[len])
                len++;
            cmds = malloc(sizeof(char *) * (len + 2));
            if (!cmds)
            {
                free(min);
                return NULL;
            }
            cmds[0] = ft_strdup(redir->cmd);
            for (i = 0; i < len; i++)
                cmds[i + 1] = ft_strdup(redir->arg[i]);
            cmds[len + 1] = NULL;
        }
        else if (heredoc && heredoc->cmd && heredoc->args)
        {
            while (heredoc->args[len])
                len++;
            cmds = malloc(sizeof(char *) * (len + 2));
            if (!cmds)
            {
                free(min);
                return NULL;
            }
            cmds[0] = ft_strdup(heredoc->cmd);
            for (i = 0; i < len; i++)
                cmds[i + 1] = ft_strdup(heredoc->args[i]);
            cmds[len + 1] = NULL;
        }
        else if ((redir && redir->cmd) || (heredoc && heredoc->cmd))
        {
            const char *cmd = redir && redir->cmd ? redir->cmd : heredoc->cmd;
            len = 1;
            cmds = malloc(sizeof(char *) * 2);
            if (!cmds)
            {
                free(min);
                return NULL;
            }
            cmds[0] = ft_strdup(cmd);
            cmds[1] = NULL;
        }
        else if (lexer && lexer->cmds)
        {
            while (lexer->cmds[len])
                len++;
            cmds = malloc(sizeof(char *) * (len + 1));
            if (!cmds)
            {
                free(min);
                return NULL;
            }
            for (i = 0; i < len; i++)
                cmds[i] = ft_strdup(lexer->cmds[i]);
            cmds[len] = NULL;
        }
        else
        {
            cmds = malloc(sizeof(char *) * 1);
            if (!cmds)
            {
                free(min);
                return NULL;
            }
            cmds[0] = NULL;
            len = 0;
        }

        // Allocate and fill type array
        min->type = malloc(sizeof(t_type) * (len + 1));
        if (!min->type)
        {
            // free cmds array
            for (i = 0; i < len; i++)
                free(cmds[i]);
            free(cmds);
            free(min);
            return NULL;
        }

        for (i = 0; i < len; i++)
        {
            // Example logic for types:
            if (redir && redir->arg)
                min->type[i] = (i == 0) ? CMD : ARGUMENT;
            else if (heredoc && heredoc->args)
                min->type[i] = (i == 0) ? CMD : ARGUMENT;
            else if (lexer && lexer->type)
                min->type[i] = lexer->type[i]; // assume lexer->type is valid array
            else
                min->type[i] = CMD; // default type
        }
        min->type[len] = -1; // sentinel, optional

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
        if (lexer)
            lexer = lexer->next;
    }

    return head;
}
