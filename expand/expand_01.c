#include "../minishell.h"

// Change signature to match minishell.h
char *expand_var(char *str, char **variabls, char **env)
{
    const char *cstr = str;
    size_t len = strlen(cstr);
    char *result = malloc(len * 10 + 1); // generous buffer size
    if (!result)
        return NULL;

    size_t ri = 0;
    size_t i = 0;
    bool in_single_quotes = false;
    bool in_double_quotes = false;

    while (cstr[i])
    {
        
        // Handle single quotes
        if (cstr[i] == '\'' && !in_double_quotes)
        {
            in_single_quotes = !in_single_quotes;
            result[ri++] = cstr[i++];
        }
        // Handle double quotes
        else if (cstr[i] == '"' && !in_single_quotes)
        {
            in_double_quotes = !in_double_quotes;
            result[ri++] = cstr[i++];
        }
        // Handle variable expansion outside single quotes and inside double quotes
        else if (cstr[i] == '$' && !in_single_quotes)
        {
            i++;
            if (cstr[i] == '\0')
                break;

            // Get the variable name
            char var_name[256];
            size_t vn_i = 0;

            while (cstr[i] && check_end(cstr[i]) && vn_i < sizeof(var_name) - 1)
                var_name[vn_i++] = cstr[i++];
            var_name[vn_i] = '\0';

            // Look up the value of the variable
            char *val = find_var_value(var_name, variabls, env);
            if (val)
            {
                size_t val_len = strlen(val);
                ft_memcpy(result + ri, val, val_len);
                ri += val_len;
            }
            else
            {
                // Variable not found, copy original
                result[ri++] = '$';
                ft_memcpy(result + ri, var_name, vn_i);
                ri += vn_i;
            }
        }
        else
        {
            result[ri++] = cstr[i++];
        }
    }
    result[ri] = '\0';
    return result;
}

char *remove_quotes(char *str)
{
    int i = 0;
    char stripped[1024];
    bool sq = false;
    bool dq = false;
    int j = 0;
    while(str[i])
    {
        sq = false;
        dq = false;
        while(str[i] != '"' && str[i] != '\'')
            stripped[j++] = str[i++];
        if(str[i] == '"')
            dq = true;
        else
            sq = true;
        if(dq)
        {
            i++;
            while(str[i] != '"')
            {
                stripped[j++] = str[i++];
            }
            i++;
        }
        else
        {
            i++;
            while(str[i] != '\'')
            {
                stripped[j++] = str[i++];
            }
            i++;
        }
    }
    stripped[j] = '\0';
    char *str1 = ft_strdup(stripped);
    return str1;
}

// Check if a character is valid in a variable name (letters, numbers, or underscores)
int check_end(char c)
{
    return (ft_isalnum((unsigned char)c) || c == '_');
}

// Find variable value from either environment variables or user-defined variables
char *find_var_value(const char *name, char **vars, char **env)
{
    size_t name_len = strlen(name);

    if (vars)
    {
        for (int i = 0; vars[i]; i++)
        {
            if (ft_strncmp(vars[i], name, name_len) == 0 && vars[i][name_len] == '=')
                return vars[i] + name_len + 1;
        }
    }
    if (env)
    {
        for (int i = 0; env[i]; i++)
        {
            if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
                return env[i] + name_len + 1;
        }
    }
    return NULL;
}