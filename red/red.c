#include "../minishell.h"

t_redir_lexer *redir_init(t_lexer *lexer)
{
    t_redir_lexer *redir_head = NULL;
    t_redir_lexer *redir_tail = NULL;

    while (lexer)
    {
        int len = 0;
        while (lexer->cmds && lexer->cmds[len])
            len++;

        char **filtered_cmds = malloc(sizeof(char *) * (len + 1));
        t_type *filtered_types = malloc(sizeof(t_type) * (len + 1));
        if (!filtered_cmds || !filtered_types)
        {
            free(filtered_cmds);
            free(filtered_types);
            return NULL;
        }

        int f_index = 0;
        int i = 0;

        while (i < len)
        {
            if (lexer->type[i] == RED_IN || lexer->type[i] == RED_OUT || lexer->type[i] == APPEND)
            {
                if (i + 1 >= len)
                {
                    // skip invalid redirection without filename
                    i++;
                    continue;
                }

                t_redir_lexer *node = malloc(sizeof(t_redir_lexer));

                node->type = lexer->type[i];
                node->file_name = ft_strdup(lexer->cmds[i + 1]);
                node->cmd = NULL;
                node->arg = NULL;
                node->next = NULL;

                if (!redir_head)
                {
                    redir_head = node;
                    redir_tail = node;
                }
                else
                {
                    redir_tail->next = node;
                    redir_tail = node;
                }

                i += 2;
            }
            else
            {
                filtered_cmds[f_index] = ft_strdup(lexer->cmds[i]);
                filtered_types[f_index] = lexer->type[i];
                f_index++;
                i++;
            }
        }
        filtered_cmds[f_index] = NULL;

        // Find command: first CMD token or first token if no CMD
        char *cmd = NULL;
        int args_start = 0;
        int j = 0;
        while (j < f_index) {
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

        // Build argument array (all tokens after command)
        int arg_count = f_index - args_start;
        char **args = NULL;
        if (arg_count > 0)
        {
            args = malloc(sizeof(char *) * (arg_count + 1));
            if (!args)
            {
                free(cmd);
                int jj = 0;
                while (jj < f_index) {
                    free(filtered_cmds[jj]);
                    jj++;
                }
                free(filtered_cmds);
                free(filtered_types);
                return redir_head;
            }
            int jj = 0;
            while (jj < arg_count) {
                args[jj] = ft_strdup(filtered_cmds[args_start + jj]);
                jj++;
            }
            args[arg_count] = NULL;
        }

        t_redir_lexer *tmp = redir_head;
        while (tmp)
        {
            if (tmp->cmd)
            {
                free(tmp->cmd);
                tmp->cmd = NULL;
            }
            tmp->cmd = ft_strdup(cmd);

            // free previous args
            if (tmp->arg)
            {
                int k = 0;
                while (tmp->arg[k])
                {
                    free(tmp->arg[k]);
                    k++;
                }
                free(tmp->arg);
                tmp->arg = NULL;
            }

            if (args)
            {
                int k = 0;
                while (args[k]) k++;
                tmp->arg = malloc(sizeof(char *) * (k + 1));
                int kk = 0;
                while (args[kk]) {
                    tmp->arg[kk] = ft_strdup(args[kk]);
                    kk++;
                }
                tmp->arg[k] = NULL;
            }
            else
            {
                tmp->arg = NULL;
            }

            tmp = tmp->next;
        }

        lexer = lexer->next;
    }

    // Print results without advancing redir_head pointer
    t_redir_lexer *print_tmp = redir_head;

    return redir_head;
}
