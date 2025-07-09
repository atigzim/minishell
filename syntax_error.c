/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:08:56 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/05 17:08:56 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] && line[i] == '|')
		return (0);
	i = if_check_pipe(line, i, '\0');
	if (i == -1)
		return (0);
	i--;
	while (i >= 0 && line[i] == ' ')
		i--;
	if (i >= 0 && line[i] == '|')
		return (0);
	return (1);
}

int	if_check_pipe(char *line, int i, char q)
{
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q = line[i++];
			while (line[i] && line[i] != q)
				i++;
			if (line[i])
				i++;
		}
		else if (line[i] == '|')
		{
			i++;
			if (line[i] && line[i] == '|')
				return (-1);
			while (line[i] && line[i] == ' ')
			{
				i++;
				if (line[i] && line[i] == '|')
					return (-1);
			}
		}
		else
			i++;
	}
	return (i);
}

int	check_split(char *line, int i, char q)
{
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q = line[i];
			i++;
			while (line[i] && line[i] != q)
				i++;
			i++;
		}
		if (line[i] == '>')
		{
			if (line[i + 1] && line[i + 1] == '>')
				return (2);
			return (1);
		}
		if (line[i] == '<')
		{
			if (line[i + 1] && line[i + 1] == '<')
				return (4);
			return (3);
		}
		i++;
	}
	return (0);
}