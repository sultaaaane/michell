/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:08:50 by mbentahi          #+#    #+#             */
/*   Updated: 2024/06/11 03:40:53 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_element	*new_element(char *line, int i,enum e_type type, enum e_state state)
{
	t_element	*element;

	element = malloc(sizeof(t_element));
	if (!element)
		return (NULL);
	element->line = ft_strndup(line, i);
	if (!element->line)
	{
		free(element);
		return (NULL);
	}
	element->type = type;
	element->state = state;
	element->next = NULL;
	element->prev = NULL;
	return (element);
}

void	add_element(t_element **lst, t_element *element)
{
	t_element	*tmp;

	if (!*lst)
	{
		*lst = element;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = element;
	element->prev = tmp;
}

void add_element_between(t_element **lst, t_element *element, t_element *prev, t_element *next)
{
    printf("add_element_between\n");
    printf("element : %s\n", element->line);
    
    // If the list is initially empty
    if (*lst == NULL)
    {
        element->next = NULL;
        element->prev = NULL;
        *lst = element;
    }
    // If adding at the beginning of a non-empty list
    else if (!prev)
    {
        element->next = *lst;
        (*lst)->prev = element;
        element->prev = NULL;
        *lst = element;
    }
    // If adding in between or at the end
    else
    {
        prev->next = element;
        element->prev = prev;
        element->next = next;
        if (next)
            next->prev = element;
    }
}

void	free_lst(t_element *lst)
{
	t_element	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

void	print_lst(t_element *lst)
{
	t_element	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("line : %s  ,", tmp->line);
		if (tmp->state == IN_SQUOTE)
			printf(" state : IN_SQUOTE , ");
		else if (tmp->state == IN_DQUOTE)
			printf(" state : IN_DQUOTE , ");
		else
			printf(" state : GENERAL , ");
		if (tmp->type == WORD)
			printf(" type : WORD\n");
		else if (tmp->type == SQUOTE)
			printf(" type : SQUOTE\n");
		else if (tmp->type == DQUOTE)
			printf(" type : DQUOTE\n");
		else if (tmp->type == PIPE)
			printf(" type : PIPE\n");
		else if (tmp->type == WHITESPACE)
			printf(" type : WHITESPACE\n");
		else if (tmp->type == OUTPUT)
			printf(" type : OUTPUT\n");
		else if (tmp->type == HERE_DOC)
			printf(" type : HERE_DOC\n");
		else if (tmp->type == APPEND)
			printf(" type : APPEND\n");
		else if (tmp->type == REDIR_IN)
			printf(" type : REDIR_IN\n");
		else if (tmp->type == REDIR_OUT)
			printf(" type : REDIR_OUT\n");
		else if (tmp->type == ENV)
			printf(" type : ENV\n");
		else if (tmp->type == NEW_LINE)
			printf(" type : NEW_LINE\n");
		tmp = tmp->next;
	}
}
