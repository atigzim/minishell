#include "../minishell.h"

char **fill_env(char **env)
{
    int i = 0;
    while(env[i])
        i++;
    
    char **variables = malloc(sizeof(char *) * (i + 1));
    if (!variables) return NULL;

    for (int idx = 0; idx < i; idx++)
    {
        char *eq_pos = strchr(env[idx], '=');
        if (!eq_pos) {
            variables[idx] = ft_strdup("");  // No '=' found: empty string
        } else {
            variables[idx] = ft_strdup(eq_pos + 1);
        }
        if (!variables[idx]) {
            // On malloc failure, cleanup previous allocations
            for (int j = 0; j < idx; j++)
                free(variables[j]);
            free(variables);
            return NULL;
        }
    }
    variables[i] = NULL;
    return variables;
}




// Expands variables in all the tokens, respecting quotes
void expand_lexer(t_lexer *lexer, char **env_var, char **env)
{
    t_lexer *current = lexer;
    while(current)
    {
        
        int i = 0;
        while(current->cmds[i])
        {
            
            // Expand variables if the string contains a '$'
            if (ft_strchr(current->cmds[i], '$'))
            {
                current->cmds[i] = expand_var(current->cmds[i], env_var, env);
            }   
            else if (ft_strchr(current->cmds[i], '"') || (ft_strchr(current->cmds[i], '$')))
                current->cmds[i] = remove_quotes(current->cmds[i]);
            i++;
         
        }
        current = current->next;
    }
}

// Expand the commands in the lexer (token list)
void expand(t_lexer *lexer, char **env)
{
    t_lexer *current = lexer;
    char **env_var;
    env_var = fill_env(env); // create environment variable list
    expand_lexer(current, env_var, env);
}