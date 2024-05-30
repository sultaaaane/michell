/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:08:50 by mbentahi          #+#    #+#             */
/*   Updated: 2024/05/29 21:36:38 by mbentahi         ###   ########.fr       */
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
		printf("line : %s\n", tmp->line);
		printf("type : %d\n", tmp->type);
		printf("state : %d\n", tmp->state);
		tmp = tmp->next;
	}
}
