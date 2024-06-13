/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:08:54 by mbentahi          #+#    #+#             */
/*   Updated: 2024/06/14 00:51:32 by mbentahi         ###   ########.fr       */
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

t_element *concatinate(t_element *element)
{
	
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