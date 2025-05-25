#include "../minishell.h"

int echo_n(char *arr)
{
    int i;

    i = 0;
    while(arr[i])
    {
        if(arr[i] != 'n')
            return (1);
        i++;
    }
    return (0);
}

void echo(t_node *com)
{
	int i;
	int j;

	i = 0;
	j = 1;
	if(!com->cmd[j])
	{
		printf("\n");
		return;
	}
	
	while (i == 0)
	{
		// printf("asjfkfhdf\n");
		i = echo_n (com->cmd[j]);
		if(i == 1)
			break;
		j++;
	}
	
	while (com->cmd[j])
	{
		printf ("%s", com->cmd[j]);
		if (com->cmd[j + 1])
			printf(" ");
		j++;
	}
	if (echo_n(com->cmd[1]) == 1)
		printf("\n");
}
