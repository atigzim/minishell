#include "../minishell.h"

void cd_execution(t_node *com)
{
    // char p[4096];
    // char *phat;

    // phat = ft_strjoin(p, "/");
    // phat = ft_strjoin(phat, arr);
    // printf("%s\n", phat);
	// getcwd(p, sizeof(p));
	// printf("%s\n", p);
    if (chdir(com->cmd[1]) == -1)
        perror("cd");
}
// int main()
// {
// 	cd_execution();
// }

