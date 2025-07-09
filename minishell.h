/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:08:50 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/05 17:08:50 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include <readline/history.h>
#include "libft/libft.h"
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include "garbage/ft_malloc.h"
# define RESET " \e[00m"

extern int	exit_code ;

typedef struct s_redi
{
    char *file_num;
    char *heredoc_file;
    int type;
    struct s_redi *next;
}t_redi;

typedef struct s_env
{
    char *key; // USER
    char *value; // atigzim
    struct s_env *next;
} t_env;

typedef struct s_data
{
    t_env *env;
    int  exit_status;
}t_data;

typedef struct s_node
{
    char **cmd;
    t_redi *file;

    struct s_node *next;
}t_node;

char *join_args(char **args);
int	minishell_init(t_node **all_cmd, char *line, t_env *info);
int	d_quote(char *line, int dquote, int quote, int i);
int	check_pipe(char *line);
int skip_quotes(char *input, int idx, int *in_double_quote);
int	handle_dollar(char **result, char *input, t_env *env_list);
char *expand_val(char *input, t_env *env_list);
char *expand_line(char *input, int in_double_quote, char *result, t_env *env_list);
char *find_end(char *dollar_start);
int	if_check_pipe(char *line, int i, char q);
int	lexer(t_node **all_cmd, char *s_line, char **p_line);
char	*fix_line(char *line);
int	handle_quotes(char *line, char *new_line, int *i, int *l);
int	handle_redirects(char *line, char *new_line, int *i, int *l);
int parse_and_tokenize(t_node **cmd_list, char *input_line, char **split_line);
int	validate_redirections(char **p_line);
int	count_commands(char **p_line);
t_node	*create_command_node(t_node *head, char **cmd, int num_cmd);
t_node	*init_node(int num_cmd);
void free_node(t_node *node);
int process_cmd(t_node *new_node, char **cmd);
t_redi *create_file(t_redi *head, char *file_num, char *check);
void set_redi_type(t_redi *new_redi, char *check);
void add_redi_to_list(t_redi *head, t_redi *new_redi);
char	*qoute_remov(char *line, char q, int i, int l);
int	check_split(char *line, int i, char q);
int	len_forma(char *line, int i, int l);
void execution(t_node *minishell);
void builtins(t_node *minishell);
pid_t   ex_com(t_node *com, char **envp);
pid_t   ex_pipe(t_node *com, char **envp);
char *give_me_a_path(t_node *com, char **env);
void storage_env(char **envp);
void env_execution(t_node *minishell);
void echo(t_node *com);
t_data *envir(void);
void export(t_node *com);
void unset(t_node *com, int j,  t_env *tmp2 );
void pwd_execution(t_node *com);
void cd_execution(t_node *com);
int check_builtins(char *s);
int open_readirections(t_node *com);
char *heredoc(t_node *min, t_redi *redi,t_env *env);
char  ** list_arr_env(t_env *env);
void loop_env(char **envp, char **line, t_env *tmp, int i);
void signal_ex();
void	ft_puterror(char *cmd, char *msg, int exit_code);
void	get_exit_code(char *cmd);
void shellvl();
void ex_signal();
void	handler_sig(int sig);
void free_unset(t_env *tmp);
void free_env();
int	count_args(char **arr);
void exit_ex(t_node *minishell);
#endif