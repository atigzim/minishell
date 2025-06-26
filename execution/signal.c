#include "../minishell.h"

void	sig_handler(int sig)
{
        write(1, "\n", 1);
        rl_on_new_line();            
        rl_replace_line("", 0);         
        rl_redisplay(); 
}
void signal_ex()
{
    signal(SIGINT,sig_handler);
    signal(SIGINT, SIG_IGN);
}