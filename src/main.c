#include "../minishell.h"

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

char    *join_args(char **args)
{
    char    *result;
    int     i;

    if (!args)
        return (NULL);
    i = 0;
    result = NULL;
    while (args[i])
    {
        result = ft_strjoin(result, args[i]);
        if(args[i + 1])
            result = ft_strjoin(result, "=");
        i++;
    }
    return (result);
}

void storage_env(t_node *com, char **envp)
{
    int i;
    t_env *tmp;
    char **line;

    if (!envp)
        return;

    i = 0;
    com->env = malloc(sizeof(t_env));
    if (!com->env)
        return;
    ft_bzero(com->env, sizeof(t_env));
    tmp = com->env;
    while (envp[i])
    {
        line = ft_split(envp[i], '=');
        if (!line)
        {
            i++;
            continue;
        }
        tmp->key = line[0];
        if (line[1] && line[2])
            tmp->value = join_args(&line[1]);
        else
            tmp->value = line[1];

        i++;
        if (envp[i])
        {
            tmp->next = malloc(sizeof(t_env));
            if (!tmp->next)
                break;
            ft_bzero(tmp->next, sizeof(t_env));
            tmp = tmp->next;
        }
        else
            tmp->next = NULL;
    }
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
        if(!test || !test->cmd[0])
            continue;
        storage_env(test, envp);
        if (ft_strcmp(test->cmd[0], "echo") == 0)
            echo(test);
        else if (ft_strcmp(test->cmd[0], "pwd") == 0)
            pwd_execution(test);
        else if (ft_strcmp(test->cmd[0], "cd") == 0)
            cd_execution(test);
        else if( ft_strcmp(test->cmd[0], "env")== 0)
            env_execution (test);
        else if (f == 1)
            ex_com(test, envp);
        else if (f > 1)
            ex_pipe(test, f, envp);
        while (test_test)
        {
            t_redi *lol = test_test->file;
            i = 0;
            while (test_test->cmd[i])
            {
                printf("cmd[ %s ]   ", test_test->cmd[i]);
                i++;
            }
            printf("\n");
            while (lol)
            {
                printf("file_num[ %s ] --> ", lol->file_num);
                if (lol->type == 0)
                    printf("type_file [ FILE_IN ]\n");
                else if (lol->type == 1)
                    printf("type_file [ FILE_OUT \n]");
                else if (lol->type == 2)
                    printf("type_file [ FILE_APPEND ]\n");
                else
                    printf("type_file [ FILE_HEREDOC ]\n");
                lol = lol->next;
            }
            printf("-------------------------------------------\n");
            test_test = test_test->next;
        }
    }
    clear_history();
}