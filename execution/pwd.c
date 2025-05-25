
#include "../minishell.h"

void pwd_execution(t_node *com)
{
	char pwd[4096];
	if(com->cmd[1] && com->cmd[1][0] == '-')
	{
			printf("no options\n");
			return ;
	}
    getcwd(pwd, sizeof(pwd));
    printf("%s\n",pwd);
	// int i;
	// i = 0;
	// while (com->env->env[i])
	// {
	// 	 printf("fhjsdgdjgdgl\n");
	// 	printf("%s\n", com->env->env[i]);
	// 	i++;
	// }
	
}

void env_execution(t_node *com)
{
	t_env *tmp;

	tmp = com->env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	
}