#include "minishell.h"

void print_par(t_min *min)
{
	int i;


 
	if(!min)
		return;
	while (min)
	{
		i = 0;
		if(min->head)
			printf("her << %s->",min->head->delimiter);
		if(min->redir_head)
			printf("file_name -> %s  type -> %u\n", min->redir_head->file_name,min->redir_head->type );
		while(min->cmds[i])
		{
			printf("min->coms %d = %s   type -> %d\n",i, min->cmds[i] , min->type[i]);
			i++;
		}
		min = min->next;
	}
	
  
}
int main(int ac, char **av, char **env)
{
	t_min *min;

	min = NULL;
	while(1)
	{
		char *str = readline("MINISHELL$: ");
		if(!str)
			exit(1);
		add_history(str);
		min = minishell(env, str);
		// printf("%s\n", min->cmds[0]);
		// print_par(min);		
		if(str)
			free(str);
	}
}
