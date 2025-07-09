/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:08:34 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/05 17:08:34 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_and_tokenize(t_node **cmd_list, char *input_line, char **split_line)
{
    char *formatted_line;
    int command_count;

    command_count = 0;
    formatted_line = fix_line(input_line);
    split_line = ft_split_space(formatted_line);
    if (validate_redirections(split_line) == 0)
    {
        ft_putendl_fd("syntax error near unexpected", 2);
        return (0);
    }
    else
    {
        command_count = count_commands(split_line);
        *cmd_list = create_command_node(*cmd_list, split_line, command_count); //return command mallocad!!
    }
    return (1);
}

char	*fix_line(char *line)
{
	char	*new_line;
	int		i;
	int		l;

	i = 0;
	l = 0;
	new_line = ft_malloc(len_forma(line, 0, 0) * sizeof(char));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			handle_quotes(line, new_line, &i, &l);
		else if (line[i] == '<' || line[i] == '>')
			handle_redirects(line, new_line, &i, &l);
		else
			new_line[l++] = line[i++];
	}
	new_line[l] = '\0';
	return (new_line);
}

int	len_forma(char *line, int i, int l)
{
	char	q;

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
		else if (ft_strchr("<>", line[i]))
		{
			l += 2;
			while (line[i] && ft_strchr("<>", line[i]))
				i++;
		}
		else
			i++;
	}
	return (l + i + 1);
}

int	handle_quotes(char *line, char *new_line, int *i, int *l)
{
	char	q;

	q = line[*i];
	new_line[(*l)++] = line[(*i)++];
	while (line[*i] && line[*i] != q)
		new_line[(*l)++] = line[(*i)++];
	if (line[*i])
		new_line[(*l)++] = line[(*i)++];
	return (1);
}

int	handle_redirects(char *line, char *new_line, int *i, int *l)
{
	new_line[(*l)++] = ' ';
	while (line[*i] && (line[*i] == '<' || line[*i] == '>'))
		new_line[(*l)++] = line[(*i)++];
	new_line[(*l)++] = ' ';
	return (1);
}
