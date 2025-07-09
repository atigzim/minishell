/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paring.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:08:53 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/05 17:08:53 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_command_node(t_node *head, char **cmd, int num_cmd)
{
	t_node	*new_node;
	t_node	*tmp;

	if (!cmd)
		return (NULL);
	new_node = init_node(num_cmd);
	if (!new_node)
		return (NULL);
	if (process_cmd(new_node, cmd) != 0)
		return (NULL);
	if (!head)
		return (new_node);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (head);
}

t_node	*init_node(int num_cmd)
{
	t_node	*new_node;

	new_node = ft_malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->cmd = (char **)ft_malloc((sizeof(char *) * (num_cmd + 1)));
	if (!new_node->cmd)
		return (NULL);
	new_node->file = NULL;
	new_node->next = NULL;
	return (new_node);
}

void free_node(t_node *node)
{
    int i;
    
    if (!node)
        return;
    if (node->cmd)
    {
        i = 0;
        while (node->cmd[i])
        {
            free(node->cmd[i]);
            i++;
        }
        free(node->cmd);
    }
    
    free(node);
}

int process_cmd(t_node *new_node, char **cmd)
{
    int i;
    int l;
    char *processed_str;
    
    i = 0;
    l = 0;
    while (cmd[i])
    {
        if (ft_strchr("<>", cmd[i][0]) && cmd[i + 1])
        {
            processed_str = qoute_remov(cmd[i + 1], 0, 0, 0);
            if (!processed_str)
                return (-1);
            new_node->file = create_file(new_node->file, processed_str, cmd[i]);
            i += 2;
        }
        else
        {
            processed_str = qoute_remov(cmd[i], 0, 0, 0);
            if (!processed_str)
                return (ft_putendl_fd("ERROR -1",2),-1);
            new_node->cmd[l++] = processed_str;
            i++;
        }
    }
    new_node->cmd[l] = NULL;
    return (0);
}

char	*qoute_remov(char *line, char q, int i, int l)
{
	char *new_line;

	new_line = ft_malloc(sizeof(char) * (ft_strlen(line) + 1));
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q = line[i++];
			while (line[i] && line[i] != q)
				new_line[l++] = line[i++];
			if (line[i])
				i++;
		}
		else
			new_line[l++] = line[i++];
	}
	new_line[l] = '\0';
	return (new_line);
}