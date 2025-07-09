/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:09:04 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/05 17:09:04 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redi	*create_file(t_redi *redir_head, char *file_num, char *check)
{
	t_redi	*new_redir;

	if (!file_num)
		return (NULL);
	new_redir = ft_malloc(sizeof(t_redi));
	if (!new_redir)
		return (NULL);
	set_redi_type(new_redir, check);
	new_redir->file_num = file_num;
    new_redir->heredoc_file = NULL;
	new_redir->next = NULL;
	if (!redir_head)
		return (new_redir);
	add_redi_to_list(redir_head, new_redir);
	return (redir_head);
}

void	set_redi_type(t_redi *new_redir, char *check)
{
	int	check_result;

	check_result = check_split(check, 0, '\0');
	if (check_result == 1)
		new_redir->type = 1;
	else if (check_result == 2)
		new_redir->type = 2;
	else if (check_result == 3)
		new_redir->type = 0;
	else if (check_result == 4)
		new_redir->type = 3;
}

void add_redi_to_list(t_redi *redir_head, t_redi *new_redir)
{
    t_redi *stor_head = redir_head;
    while (stor_head->next)
        stor_head = stor_head->next;
    stor_head->next = new_redir;
}
