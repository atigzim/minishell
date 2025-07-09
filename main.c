/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:08:43 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/05 17:08:43 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exit_code = 0;

void free_env()
{
    printf("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh\n");
    t_env *env;
    t_env *temp;

    env = envir()->env;
    while(env)
    {
        temp = env->next;
        free_unset(env);
        env = temp;
    }
}
int main(int ac,char **av, char **envp)
{

    (void)ac;
    (void)av;
    char *line;
    t_env *env = NULL;
    t_node *head = NULL;

    signal_ex();
    if (!envir()->env)
    {
        storage_env(envp);
        shellvl(); 
    }
    while (1)
    {
        head = NULL;
        line = readline("MINSHELL : ");
        if (!line)
        {
            free_garbage();
            free_env();
            return (0);
        }
        if(!env)
            env = envir()->env;
        add_history(line);
        if(minishell_init(&head, line, env) == 1)
            free_garbage();
        else
            execution(head);
        
    }
    clear_history();
}
