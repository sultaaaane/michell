/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:08:54 by mbentahi          #+#    #+#             */
/*   Updated: 2024/06/27 21:57:17 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"


int count_nodes(t_element *curr)
{
	int count = 0;
	while(curr && curr->type != WHITESPACE 
	&& curr->type != PIPE && curr->type != REDIR_IN 
	&& curr->type != REDIR_OUT && curr->type != APPEND
	&& curr->type != HERE_DOC) 
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

// t_element *concatinate(t_element *element)
// {
	
// }

t_element *join_inquotes(t_element *element)
{
	t_element *new;
	char *line;
	t_element *curr;

	new = NULL;
	curr = element;
	while (curr)
	{
		if ((curr->type == SQUOTE || curr->type == DQUOTE) && curr->state == GENERAL)
		{
			line = NULL;
			curr = curr->next;
			while (curr && curr->state != GENERAL)
			{
				printf("enter\n");
				line = ft_strjoin(line, curr->line);
				curr = curr->next;
			}
			if (line)
				add_element(&new, new_element(line, ft_strlen(line), WORD, curr->prev->state));
			free(line);
		}
		else
		{
			add_element(&new, new_element(curr->line, ft_strlen(curr->line), curr->type, curr->state));
			curr = curr->next;
		}
	}
	free_lst(element);
	return (new);
}

t_element *without_quotes(t_element *element)
{
	t_element *new;

	new = NULL;
	while (element)
	{
		if ((element->type == SQUOTE || element->type == DQUOTE) && element->state == GENERAL)
		{
			element = element->next;
		}
		if (element)
		{
			add_element(&new, new_element(element->line, ft_strlen(element->line), element->type, element->state));
			element = element->next;
		}
	}
	free_lst(element);
	return (new);
}

void	check_concate(t_element **element)
{
	t_element *curr = *element;

	while(curr)
	{
		if(curr->type != WHITESPACE && curr->type != PIPE && curr->type != REDIR_IN 
			&& curr->type != REDIR_OUT && curr->type != APPEND
			&& curr->type != HERE_DOC && count_nodes(curr) > 1)
		{	
			printf("CONCATED\n");
			curr = curr->next;
		}
		else if(curr->type != WHITESPACE)
			curr = curr->next;
		else
		{
			printf("NOT CONCAT\n");
			curr = curr->next;
		}
	}
}