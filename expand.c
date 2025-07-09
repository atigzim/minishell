/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:08:30 by atigzim           #+#    #+#             */
/*   Updated: 2025/07/05 17:08:30 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_line(char *input, int in_double_quote, char *result, t_env *env_list)
{
    int segment_len;
    char *segment;
    char *temp_result;
    
    while (input && *input)
    {
        segment_len = 0;
        while (input[segment_len] && input[segment_len] != '$')
            segment_len = skip_quotes(input, segment_len, &in_double_quote);
        segment = ft_substr(input, 0, segment_len);
        temp_result = ft_strjoin_ga(result, segment);
        result = temp_result;
        if (input[segment_len] == '$')
        {
            input += segment_len;
            segment_len = handle_dollar(&result, input, env_list);
        }
        input += segment_len;
    }
    return (result);
}

int skip_quotes(char *input, int idx, int *in_double_quote)
{
    if (input[idx] == '"')
    {
        *in_double_quote = !(*in_double_quote);
        idx++;
    }
    else if (input[idx] == '\'' && !(*in_double_quote))
    {
        idx++;
        while (input[idx] && input[idx] != '\'')
            idx++;
        if (input[idx])
            idx++;
    }
    else
        idx++;
    return (idx);
}

int handle_dollar(char **result, char *input, t_env *env_list)
{
    int var_len = 1;
    char *expanded_value;

    expanded_value = expand_val(input, env_list);
    *result = ft_strjoin_ga(*result, expanded_value);
    if (input[var_len] && (input[var_len] == '?' || ft_isdigit(input[var_len])))
        var_len++;
    else if (input[var_len] == '$')
    {
        while (input[var_len] == '$')
            var_len++;
        var_len--;
    }
    else
    {
        while (input[var_len] && ft_isalnum(input[var_len]))
            var_len++;
    }
    return (var_len);
}

char *expand_val(char *input, t_env *env_list)
{
    char *dollar_pos;
    char *env_key;
    t_env *env_node;

    dollar_pos = ft_strnstr(input, "$", ft_strlen(input));
    if (!dollar_pos)
        return (NULL);
    if (!dollar_pos[1])
        return (ft_strdup_ga("$"));
    if (dollar_pos[1] == '$')
        return (ft_strdup_ga("$") );
    env_key = find_end(dollar_pos);
    if (!env_key)
        return (NULL);
    env_node = env_list;
    while (env_node)
    {
        if (ft_strcmp(env_node->key, env_key) == 0)
        {
            return (env_node->value ? ft_strdup_ga(env_node->value) : ft_strdup_ga(""));
        }
        env_node = env_node->next;
    }
    if (dollar_pos[1] && dollar_pos[1] == '?')
        return (ft_itoa(exit_code));
    if (dollar_pos[1] && !ft_isalnum(dollar_pos[1]))
        return (ft_strdup_ga("$"));
    return (ft_strdup_ga(""));
}

char *find_end(char *dollar_start)
{
    int key_len = 1;

    while (dollar_start[key_len] && (ft_isalnum(dollar_start[key_len]) || dollar_start[key_len] == '_'))
        key_len++;
    return ft_substr(dollar_start + 1, 0, key_len - 1);
}