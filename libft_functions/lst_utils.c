#include "../minishell.h"

t_token	*lst_store(void *content, int index)
{
    t_token	*new_node;

    new_node = malloc(sizeof(t_token));
    if (!new_node)
        return NULL;

    char *str_content = (char *)content;
    new_node->value = ft_strdup(str_content);
    if (!new_node->value)
    {
        free(new_node);
        return NULL;
    }
    new_node->index = index;
    new_node->next = NULL;
    return new_node;
}