#include "../../minishell.h"

void pwd_execution(t_min *com)
{
	char pwd[4096];
	if(com->cmds[1] && com->cmds[1][0] == '-')
	{
			printf("no options\n");
			return ;
	}
    getcwd(pwd, sizeof(pwd));
    printf("%s\n",pwd);
}