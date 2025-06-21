#include "minishell.h"

bool syntax_errors(char *str)
{
   
    if(!pipe_error(str))
        return false;
    if(!check_quotes(str))
        return false;
    if(!check_redirects(str))
        return false;
    return true;
     
}

bool check_redirects(char *str)
{
    int i = 0;
    int j = 0;
    int red = 0;;
    while (str[j] && str[j] != '|')
    {
        if(str[j] == '<' || str[j] == '>')
            i = red = j;
        // printf("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh\n");
        j++;
    }
    i++;
    if(!str[i] || i == j)
        return false;
    while(str[i] && i < j)
    {
        if(str[i] == ' ' || str[i] == '\t' && i < j)
        {
            while(str[i] == ' ' || str[i] == '\t' && i < j)
                i++;
            if(!str[i] || i == j)
            {
                fprintf(stderr, "Error: Missing file name after redirect\n");
                return false;
            }
        }
        break;
    }

    return true;
}

bool check_quotes(char *str)
{
    int i = 0;
    while (str[i])
    {
        if(str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
            if (str[i] != '\'')
            {
                fprintf(stderr, "Error: Unmatched single quote\n");
                return false;
            }
        }
        else if (str[i] == '\"')
        {
            i++;
            while (str[i] && str[i] != '\"')
                i++;
            if (str[i] != '\"')
            {
                fprintf(stderr, "Error: Unmatched double quotesssss\n");
                return false;
            }
        }
        i++;
    }
    return true;
}

bool pipe_error(char *str)
{
    int i = 0;
    while(str[i] == ' ' || str[i] == '\t')
        i++;
    if(str[i] == '|')
    {
        fprintf(stderr, "Error: Command cannot start with a pipe\n");
        return false;
    }
    i = ft_strlen(str) - 1;
    while(i >= 0 && (str[i] == ' ' || str[i] == '\t'))
        i--;
    if(str[i] == '|')
    {
        fprintf(stderr, "Error: Command cannot end with a pipe\n");
        return false;
    }
    return true;
}