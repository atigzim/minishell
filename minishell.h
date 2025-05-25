
#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <stdio.h>
#include "libft/libft.h"


typedef enum e_file_type
{
    FILE_IN,      // <  = 0
    FILE_OUT,     // >  = 1
    FILE_APPEND,  // >> = 2
    FILE_HEREDOC, // << = 3
} t_file_type;
typedef struct s_env
{
    char *key; // USER
    char *value; // atigzim
    // USER=atigzim
    // printf("%s=%s")
    struct s_env *next;
} t_env;

typedef struct s_redi
{
    char *file_num;
    t_file_type type;
    struct s_redi *next;
}t_redi;

typedef struct s_node
{
    char **cmd;
    t_redi *file;
    t_env *env;
    struct s_node *next;
}t_node;

/*-----------------------------------------   syntax_erroe   ------------------------------------*/

int check_split(char *line, int i, char q);
int d_quote(char *line, int dquote, int quote, int i);
int check_pipe(char *line);
int if_check_pipe(char *line, int i, char q);

/*--------------------------------------------   lexer   ----------------------------------------*/

int lexer(t_node **test, char *s_line ,char **p_line);
int len_forma(char *line, int i, int l);
char *fix_line(char *line);
int check_redirections(char **p_line);
int num_cmd(char **p_line);

/*--------------------------------------------   parser   ----------------------------------------*/

t_redi *creat_file(t_redi *head, char *file_num, char *check);
t_node *init_node(int num_cmd);
t_node *creat_node(t_node *head, char **cmd, int num_cmd);

/*--------------------------------------------   expand   ----------------------------------------*/

char *find_end(char *start);
char *expand_val(char *s);
char *expand_line(char *line, int dquote , char *plus);
char *qoute_remov(char *line);
/*--------------------------------------------   execution   ----------------------------------------*/
void ex_com(t_node *com, char **envp);
char *give_me_a_path(t_node *com, char **envp);
void ex_pipe(t_node *com,int i, char **envp);
void ex_pipe(t_node *com, int count, char **envp);
void echo(t_node *com);
void pwd_execution(t_node *com);
void cd_execution(t_node *com);
int	ft_strcmp(const char *s1, const char *s2);
void env_execution(t_node *com);

#endif