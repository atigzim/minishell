/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:06:38 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/06 20:15:29 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void pwd_execution(t_node *com)
{
	char pwd[4096];
	if(com->cmd[1] && com->cmd[1][0] == '-' && com->cmd[1][1])
	{
			exit_code = 1;
			printf("no options\n");
			return ;
	}
    getcwd(pwd, sizeof(pwd));
    printf("%s\n",pwd);
	exit_code = 0;
}
