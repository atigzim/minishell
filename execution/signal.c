/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:08:21 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/07 23:01:55 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int sig)
{
        exit_code = 130;
        write(1, "\n", 1);
        rl_on_new_line();            
        rl_replace_line("", 0);         
        rl_redisplay(); 
}
void	handler_sig(int sig)
{
        exit_code = 130;
        write(1, "\n", 1);
}
void ex_signal()
{
    signal(SIGINT, SIG_IGN);
    signal(SIGINT,handler_sig);
}
void signal_ex()
{
    signal(SIGINT, SIG_IGN);
    signal(SIGINT,sig_handler);
}