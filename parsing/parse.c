/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:08:54 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/09 18:19:17 by mbentahi         ###   ########.fr       */
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

char *concatinate(t_element **element)
{
	char *concated;
	char *tmp;

	concated = NULL;
	while (*element && (*element)->type != WHITESPACE && (*element)->type != PIPE && (*element)->type != REDIR_IN 
			&& (*element)->type != REDIR_OUT && (*element)->type != APPEND
			&& (*element)->type != HERE_DOC)
	{
		tmp = ft_strjoin_concate(concated, (*element)->line);
		free(concated);
		concated = tmp;
		*element = (*element)->next;
	}
	return (concated);
}

t_element *join_inquotes(t_element *element)
{
	t_element *new;
	char *line;
	t_element *curr;

	new = NULL;
	curr = element;
	while (curr)
	{
		if (curr && (curr->type == SQUOTE || curr->type == DQUOTE) && curr->state == GENERAL)
		{
			line = NULL;
			curr = curr->next;
			while (curr && curr->state != GENERAL)
			{
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
		if (element && (element->type == SQUOTE || element->type == DQUOTE) && element->state == GENERAL)
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

t_element	*check_concate(t_element **element)
{
	t_element *curr = *element;
	t_element *new;
	char *concated;

	new = NULL;
	while(curr)
	{
		if(curr && curr->type != WHITESPACE && curr->type != PIPE && curr->type != REDIR_IN 
			&& curr->type != REDIR_OUT && curr->type != APPEND
			&& curr->type != HERE_DOC && curr->type != ENV && count_nodes(curr) > 1)
		{
			// printf("CONCAT\n");
			concated = concatinate(&curr);
			if (concated)
			{
				add_element(&new, new_element(concated, ft_strlen(concated), CONCATE, GENERAL));
				free(concated);
			}
		}
		else if(curr && curr->type == WHITESPACE)
			curr = curr->next;
		else
		{
			// printf("NOT CONCAT\n");
			// printf("line : %s  \n", curr->line);
			add_element(&new, new_element(curr->line, ft_strlen(curr->line), curr->type, curr->state));
			curr = curr->next;
		}
	}
	free_lst(*element);
	return (new);
}

void end_of_file(t_element **element)
{
	t_element *curr = *element;
	int i = 0;
	
	while (curr && curr->next && i != 1)
	{
		if (curr->type == HERE_DOC)
		{
			while (curr && curr->type != WHITESPACE && curr->type != PIPE && curr->type != REDIR_IN)
			{
				if (curr->next && (curr->next->type == WORD || curr->next->type == ENV))
				{
					i = 1;
					curr->next->type = END_OF_FILE;
					break;
				}
				curr = curr->next;
			}
		}
		else
			curr = curr->next;
	}
}
