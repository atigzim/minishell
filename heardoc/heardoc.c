#include "../minishell.h"

t_heredoc *heardoc_init(t_lexer *lexer)
{
    t_heredoc *head = NULL;
    t_heredoc *tail = NULL;

    while (lexer)
    {
        int len = 0;
        while (lexer->cmds && lexer->cmds[len])
            len++;

        // For storing non-heredoc tokens
        char **filtered_cmds = malloc(sizeof(char *) * (len + 1));
        t_type *filtered_types = malloc(sizeof(t_type) * (len + 1));
        if (!filtered_cmds || !filtered_types)
            return NULL;

        int f_index = 0;
        int i = 0;

        // Loop through tokens
        while (i < len)
        {
            if (lexer->type[i] == HERE_DOC)
            {
                // Sanity check
                if (i + 1 >= len)
                {
                    i++;
                    continue;
                }

                // Create new heredoc node
                t_heredoc *node = malloc(sizeof(t_heredoc));
                if (!node)
                    return head;

                node->delimiter = ft_strdup(lexer->cmds[i + 1]);
                node->cmd = NULL;
                node->args = NULL;
                node->next = NULL;

                // Add node to linked list
                if (!head)
                {
                    head = node;
                    tail = node;
                }
                else
                {
                    tail->next = node;
                    tail = node;
                }

                i += 2; // Skip heredoc operator and delimiter
            }
            else
            {
                // Keep as possible command/arg
                filtered_cmds[f_index] = ft_strdup(lexer->cmds[i]);
                filtered_types[f_index] = lexer->type[i];
                f_index++;
                i++;
            }
        }
        filtered_cmds[f_index] = NULL;

        // Find the command in filtered tokens
        char *cmd = NULL;
        int args_start = 0;
        int j = 0;
        while (j < f_index)
        {
            if (filtered_types[j] == CMD)
            {
                cmd = ft_strdup(filtered_cmds[j]);
                args_start = j + 1;
                break;
            }
            j++;
        }
        if (!cmd && f_index > 0)
        {
            cmd = ft_strdup(filtered_cmds[0]);
            args_start = 1;
        }

        // Collect arguments after the command
        int arg_count = f_index - args_start;
        char **args = NULL;
        if (arg_count > 0)
        {
            args = malloc(sizeof(char *) * (arg_count + 1));
            int jj = 0;
            while (jj < arg_count)
            {
                args[jj] = ft_strdup(filtered_cmds[args_start + jj]);
                jj++;
            }
            args[arg_count] = NULL;
        }

        // Assign cmd and args to each heredoc node
        t_heredoc *temp = tail;
        while (temp && temp->cmd == NULL)
        {
            temp->cmd = ft_strdup(cmd);
            if (args)
            {
                int k = 0;
                while (args[k]) k++;
                temp->args = malloc(sizeof(char *) * (k + 1));
                int kk = 0;
                while (kk < k)
                {
                    temp->args[kk] = ft_strdup(args[kk]);
                    kk++;
                }
                temp->args[k] = NULL;
            }
            temp = temp->next;
        }

        lexer = lexer->next;
    }

    t_heredoc *tmp = head;
    return head;
}
