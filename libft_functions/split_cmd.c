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

char **split_cmd(char *str)
{
    const char *s = str;
    char *tokens[1024];
    int count = 0, len, i = 0;
    const char *start;

    while (*s) {
        skip_spaces(&s);
        if (*s == '\0')
            break;

        // Handle operators as separate tokens
        int op_len = is_operator(s);
        if (op_len) {
            tokens[count++] = strndup(s, op_len);
            s += op_len;
            continue;
        }

        // Start of a new token
        start = s;
        len = 0;
        while (s[len] && !ft_isspace(s[len]) && !is_operator(s + len)) {
            if (s[len] == '\'' || s[len] == '"') {
                char quote = s[len];
                len++; // include the opening quote
                while (s[len] && s[len] != quote) {
                    len++;
                }
                if (s[len] == quote)
                    len++; // include the closing quote
            } else {
                len++;
            }
        }
        tokens[count++] = strndup(start, len);
        s += len;
    }

    tokens[count] = NULL;

    char **result = malloc((count + 1) * sizeof(char *));
    for (i = 0; i < count; i++) {
        result[i] = tokens[i];
    }
    result[count] = NULL;

    return result;
}
