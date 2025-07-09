/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:06:14 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/07 02:02:54 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int echo_n(char *arr)
{
    int i;

    i = 0;
	if(!arr)
		return (1);
    if(arr[i] == '-' && arr[i + 1] != 'n')
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

void echo(t_node *com)
{
    int (i), (j), (is_error);

    i = 0;
    j = 1;
    is_error = 0;
    if(!com->cmd[j])
    {
        is_error = printf("\n");
        return;
    }
	if (com->cmd[j][0] == '\0')
	{
		is_error = printf(" ");
		j++;
	}
    while (com->cmd[j])
    {
        i = echo_n (com->cmd[j]);
        if(i == 1)
            break;
        j++;
    }
    while (com->cmd[j])
    {
        is_error = printf ("%s", com->cmd[j]);
        if (com->cmd[j + 1])
            is_error = printf(" ");
        j++;
    }
    if (echo_n(com->cmd[1]) == 1)
        is_error = printf("\n");
    if (is_error == -1)
    {
        write(2, "minishell: echo: write error: No space left on device\n", 55);
        exit_code = 1;
    }
    else
        exit_code = 0;
}
