#include "../../minishell.h"

int echo_n(char *arr)
{
    int i;

    i = 0;
	if(!arr)
		return (1);
    if (arr[i] == '-')
        i++;
    while(arr[i])
    {
        if(arr[i] != 'n')
            return (1);
        i++;
    }
	if (arr[0] == '\0')
		return (1);
    return (0);
}

void echo(t_lexer *com)
{
    int (i), (j);

    i = 0;
    j = 1;
    if(!com->cmds[j])
    {
        printf("\n");
        return;
    }
	if (com->cmds[j][0] == '\0')
	{
		printf(" ");
		j++;
	}
    while (com->cmds[j])
    {
        i = echo_n (com->cmds[j]);
        if(i == 1)
            break;
        j++;
    }
    while (com->cmds[j])
    {
        printf ("%s", com->cmds[j]);
        if (com->cmds[j + 1])
            printf(" ");
        j++;
    }
    if (echo_n(com->cmds[1]) == 1)
        printf("\n");
}
