#include "minishell.h"

int main(int ac, char **av, char **env)
{
    t_lexer *lexer;
    lexer = NULL;
    storage_env(env);
    while(1)
    {
        char *str = readline("MINISHELL$: ");
        if(!str)
            exit(1);
        add_history(str);
        lexer = minishell(env, str);
        execution(lexer);
        if(str)
            free(str);
    }
}