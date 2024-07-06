/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:24:21 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/06 20:17:51 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int is_redirection(t_type type)
{
    return (type == REDIR_IN || type == REDIR_OUT || type == APPEND || type == HERE_DOC);
}

void handle_redirection(t_element *elem, t_element **next, int *fd_in, int *fd_out)
{
    *next = elem->next;
    if (*next && (*next)->type == WORD)
    {
        if (elem->type == REDIR_IN)
            *fd_in = open((*next)->line, O_RDONLY);
        else if (elem->type == REDIR_OUT)
            *fd_out = open((*next)->line, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (elem->type == APPEND)
            *fd_out = open((*next)->line, O_WRONLY | O_CREAT | O_APPEND, 0644);
        // Handle HERE_DOC separately as it's more complex
    }
    *next = (*next)->next; // Move to the next element after the filename
}

int count_command_size(t_element *elem)
{
    int cmd_size = 0;

    while (elem && (elem->type == WORD || elem->type == CONCATE))
    {
        cmd_size++;
        elem = elem->next;
    }
    return (cmd_size);
}

char **concate_join_command(t_element *elem)
{
    
    char **full_command = NULL;
    char *command = NULL;

    while (elem && (elem->type == WORD || elem->type == CONCATE))
    {
        command = ft_strjoin(command, elem->line);
        command = ft_strjoin(command, " ");
        elem = elem->next;
    }
    full_command = ft_split(command, ' ');
    free(command);
    return (full_command);
}

t_parse *process_elements(t_element *elements)
{
    t_parse *head = NULL;
    t_element *elem = elements;
    char **command = NULL;
    int fd_in = STDIN_FILENO;
    int fd_out = STDOUT_FILENO;

    while (elem)
    {
        if (elem->type == REDIR_IN || elem->type == REDIR_OUT || elem->type == APPEND)
            handle_redirection(elem, &elem, &fd_in, &fd_out);
        else if (elem->type == WORD || elem->type == CONCATE)
        {
            command = concate_join_command(elem);
            t_parse *new = malloc(sizeof(t_parse));
            new->fd_in = fd_in;
            new->fd_out = fd_out;
            new->full_command = command;
            new->next = NULL;
            new->prev = NULL;
            while (elem && (elem->type == WORD || elem->type == CONCATE))
                elem = elem->next;
            fd_in = STDIN_FILENO;
            fd_out = STDOUT_FILENO;
        }
            elem = elem->next;
    }

    return (head);
}