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

typedef struct s_lexer
{
	char    	*str;
	char **cmds;
	t_type		*type;
	bool		squote;
	bool		dquote;
	bool		expand;
	bool append;
	bool here_doc;
	bool red_in;
	int		i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;


// main functions
t_lexer *minishell(char **env, char *str);
t_lexer *lexer_init(char *str, t_token **tokens);

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
void	ft_bzero(void *s, size_t n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_isalpha(int c);

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
bool check_expansion(char *str);
char *handle_quotes(char *str);
char *expand_vr(char *str, char **variables, char **env);
void expand_variabls(t_lexer *head, char **variables , char **env);


// ............excut
void execution(t_lexer *minishell);
typedef struct s_env
{
    char *key; // USER
    char *value; // atigzim
    // USER=atigzim
    // printf("%s=%s")
    struct s_env *next;
} t_env;

typedef struct s_data
{
    t_env *env;
    int  exit_status;
}t_data;
void storage_env(char **envp);
void env_execution(t_lexer *minishell);
void echo(t_lexer *com);
t_data *envir(void);
void export(t_lexer *com);

#endif