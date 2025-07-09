/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:09:00 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/05 17:09:00 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int minishell_init(t_node **all_cmd, char *line, t_env *info)
{
    char	**split_line;
	char	*expanded_line;
	int		idx;

	expanded_line = NULL;
	idx = 0;
	if (!d_quote(line, 0, 0, 0) || !check_pipe(line))
	{
		exit_code = 2;
		ft_putendl_fd("syntax error near unexpected", 2);
		return (1);
	}
	else
	{
		expanded_line = expand_line(line, 0, ft_strdup_ga(""), info);
		if (expanded_line)
		{
			split_line = ft_split_ga(expanded_line, '|');	
		}
		while (split_line[idx])
		{
			if (!parse_and_tokenize(all_cmd, split_line[idx], NULL))
				break ;
			idx++;
		}
	}
	return (0);
}

int	d_quote(char *line, int dquote, int quote, int i)
{
	char	q;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q = line[i++];
			if (q == '\"')
				dquote++;
			else
				quote++;
			while (line[i] && line[i] != q)
				i++;
			if (line[i] == '\0')
				break ;
			if (line[i] == '\"')
				dquote++;
			if (line[i] == '\'')
				quote++;
		}
		i++;
	}
	if (dquote % 2 != 0 || quote % 2 != 0)
		return (0);
	return (1);
}

int	validate_redirections(char **p_line)
{
	int	i;

	i = 0;
	if (p_line[0] && ft_strchr("<>", p_line[0][0]) && !p_line[1])
		return (0);
	while (p_line[i])
	{
		if (ft_strchr("<>", p_line[i][0]))
		{
			if (p_line[i][1] && ft_strchr("<>", p_line[i][1]))
			{
				if (p_line[i][1] != p_line[i][0])
					return (0);
				else if (p_line[i][2])
					return (0);
			}
			else if (p_line[i + 1] && ft_strchr("<>", p_line[i + 1][0]))
				return (0);
		}
		i++;
	}
	if (i > 0 && p_line[i - 1] && ft_strchr("<>", p_line[i - 1][0]))
		return (0);
	return (1);
}

int	count_commands(char **p_line)
{
	int	num_cmd;
	int	l;

	num_cmd = 0;
	l = 0;
	while (p_line[l])
	{
		if (ft_strchr("<>", p_line[l][0]))
		{
			num_cmd--;
			l++;
		}
		else
		{
			num_cmd++;
			l++;
		}
	}
	return (num_cmd);
}