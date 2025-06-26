#include "minishell.h"

t_lexer *lexer_init(char *str, t_token **tokens)
{
    char **cmds = ft_split(str, '|');
    int i = 0;
    int j = 0;
    t_lexer *head = NULL;
    t_lexer *prev = NULL;
    
    
    while (cmds[i])
    {
         
        t_lexer *lexer = malloc(sizeof(t_lexer));
        if (!lexer)
            return NULL;
        lexer->str = ft_strdup(cmds[i]);
        lexer->cmds = split_cmd(cmds[i]);
        j = 0;
       
        while(lexer->cmds[j])
            j++;
        lexer->type = malloc(sizeof(t_type) * j + 1);
        j = 0;
        while(lexer->cmds[j])
        {
            lexer->type[j] = check_type(lexer->cmds[j], tokens);
            j++;
        }
        lexer->type[j] = 0;
        lexer->i = i;
        lexer->prev = prev;
        lexer->next = NULL;

        if (prev)
            prev->next = lexer;
        else
            head = lexer;

        prev = lexer;
        i++;
    }
   
    return head;
}

t_min *minishell(char **env, char *str)
{
    t_token *tokens;
    t_lexer *lexer;
    lexer = NULL;
    tokens = NULL;
    if(!syntax_errors(str))
    {
        printf("Error: syntax error\n");
        return (NULL);
    }
    if(!split_store(str, &tokens))
    {
        fprintf(stderr, "Error: allocation failed while tokenizing\n");
        return (NULL);
    }
    lexer = lexer_init(str, &tokens);
    t_lexer *tmp = lexer;
    expand(tmp, env);
    t_redir_lexer *redir = NULL;
    redir = redir_init(lexer);
    t_heredoc *heredoc = heredoc_init(lexer);
    t_min *min = inti_min(redir, heredoc, lexer);
    int i = 0;
    return (min);
}