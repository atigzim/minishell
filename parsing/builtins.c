#include "../minishell.h"

bool check_builtin(char *str)
{
    const char *builtins[] = {
        "cd", "echo", "env", "exit", "export", "pwd", "unset", NULL
    };

    int i = 0;
    while(builtins[i])
    {
        if (ft_strcmp(builtins[i], str) == 0)
            return true;
        i++;
    }
    return false;
}