#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>


typedef enum s_type
{
	CMD,
	ARGUMENT,
	BUILTIN,
	PIPE,
	HERE_DOC,
	APPEND,
	RED_IN,
	RED_OUT,
	FILE_NAME
}						t_type;

typedef struct s_token
{
    char			*value;
	int			index;
	struct s_token	*next;
}						t_token;

typedef struct s_redir_lexer
{
    char *file_name;
    t_type type;
	// char *cmd;
	// char **arg;
    struct s_redir_lexer *next;
} t_redir_lexer;

typedef struct s_lexer
{
	char    	*str;
	char **cmds;
	t_type		*type;
	int		i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_heredoc
{
	char *delimiter;
	bool expanded; // Indicates if the delimiter has been expanded
	// char *cmd;
	// char **args;
	struct s_heredoc *next;
} t_heredoc;

typedef struct min
{
	t_hearedoc *head;
	t_redir_lexer *redir_head;
	char **cmds;
}
// main functions
void minishell(char **env, char *str);
t_lexer *lexer_init(char *str, t_token **tokens);

// redirection functions
t_redir_lexer *redir_init(t_lexer *lexer);

// heredoc functions
t_heredoc *heardoc_init(t_lexer *lexer);

// libft functions
size_t	ft_strlen(const char *str);
char **split_cmd(char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
t_token	*lst_store(void *content, int index);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
int ft_strcmp(char const *s1, char const *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strchr(const char *s, int c);
int	ft_strncmp(char *s1, const char *s2, unsigned int n);
int	ft_isalnum(int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);

// syntax error checking functions
bool syntax_errors(char *str);
bool pipe_error(char *str);
bool check_quotes(char *str);
bool check_redirects(char *str);

// tokenization functions
bool split_store(char *str, t_token **head);

// parsing functions
t_type check_type(char *str, t_token **tokens);
bool check_cmd(char *str, t_token **tokens);
bool check_builtin(char *str);
bool check_file_name(char *str, t_token **tokens);

// expand functions
void expand(t_lexer *lexer, char **env);
char *find_var_value(const char *name, char **vars, char **env);
char *remove_quotes(char *str);;
char *expand_var(char *str, char **vars, char **env);
int check_end(char c);

#endif