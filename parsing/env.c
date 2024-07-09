/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:18:29 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/09 13:07:39 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_env *create_env_node(char *key, char *value)
{
    t_env *node = malloc(sizeof(t_env));
    if (!node)
        return NULL;
    node->key = ft_strdup(key);
    node->value = ft_strdup(value);
    node->next = NULL;
    return node;
}

t_env *build_env_list(char **envp)
{
    t_env *head = NULL;
    t_env *tail = NULL;
    char **key_value;
    int i = 0;
    while (envp[i])
    {
        key_value = ft_split(envp[i], '=');
        if (!key_value || !key_value[0] || !key_value[1])
            return (ft_free2d(key_value),NULL);
        t_env *node = create_env_node(key_value[0], key_value[1]);
        ft_free2d(key_value);
        if (!node)
            return (ft_free2d(key_value),NULL);
        if (!head)
            head = node;
        else
            tail->next = node;
        tail = node;
        i++;
    }
    // ft_free2d(key_value);
    return (head);
}

void ft_free_env(t_env *env)
{
    t_env *tmp;
    while (env)
    {
        tmp = env;
        env = env->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}
