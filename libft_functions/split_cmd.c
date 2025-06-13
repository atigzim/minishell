#include "../minishell.h"

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t');
}

static int is_operator(const char *s)
{
    if (!s)
        return 0;
    if (s[0] == '<' && s[1] == '<')
        return 2;
    if (s[0] == '>' && s[1] == '>')
        return 2;
    if (s[0] == '<' || s[0] == '>' || s[0] == '|')
        return 1;
    return 0;
}

static void skip_spaces(const char **s)
{
    while (**s == ' ' || **s == '\t')
        (*s)++;
}

static int get_token_len(const char *s)
{
    int len = 0;

    if (s[0] == '\'') {
        len++; // skip opening '
        while (s[len] && s[len] != '\'')
            len++;
        if (s[len] == '\'')
            len++; // include closing '
        return len;
    }
    else if (s[0] == '"') {
        len++; // skip opening "
        while (s[len] && s[len] != '"')
            len++;
        if (s[len] == '"')
            len++; // include closing "
        return len;
    }

    while (s[len]) {
        if (ft_isspace(s[len]) || is_operator(s + len) || s[len] == '\'' || s[len] == '"')
            break;
        len++;
    }

    return len;
}


char **split_cmd(char *str)
{
    const char *s = str;
    char *tokens[1024];
    int count = 0, op_len, len, i = 0;
    const char *start;

    while (*s) {
        skip_spaces(&s);
        if (*s == '\0')
            break;

        op_len = is_operator(s);
        if (op_len) {
            tokens[count++] = strndup(s, op_len);
            s += op_len;
        }
        else if (*s == '\'' || *s == '"') {
            len = get_token_len(s);
            tokens[count++] = strndup(s, len);
            s += len;
        }
        else {
            len = get_token_len(s);
            tokens[count++] = strndup(s, len);
            s += len;
        }
    }

    tokens[count] = NULL;

    char **result = malloc((count + 1) * sizeof(char *));
    while (i < count) {
        result[i] = tokens[i];
        i++;
    }
    result[count] = NULL;

    return result;
}
