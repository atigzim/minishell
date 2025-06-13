#include "../minishell.h"

static int var_len(char *str)
{
    int len = 0;
    while (str[len] && str[len] != '=')
        len++;
    return len;
}

static char **vr_split(char **env)
{
    int i = 0;
    while(env[i])
    {
        i++;
    }
    char **variables = malloc(sizeof(char *) * (i + 1));
    if (!variables)
        return NULL;
    i = 0;
    while (env[i])
    {
        int len = var_len(env[i]);
        variables[i] = malloc(len + 1);
        variables[i] = ft_strncpy(variables[i], env[i], len);
        variables[i][len] = '\0';
        i++;
    }
    variables[i] = NULL;
    return variables;
}

void expand(t_lexer *lexer, char **env)
{
    char **variables;
    variables = vr_split(env);
    t_lexer *tmp = lexer;
    expand_variabls(tmp, variables, env);
    // while (lexer)
    // {
    //     int i = 0;
    //     while(lexer->cmds[i])
    //     {
    //         printf("%s", lexer->cmds[i]);
    //         i++;
    //     }
    //     lexer = lexer->next;
    // }
    // printf("\n");
    
}