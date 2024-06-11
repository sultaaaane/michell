/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:23:43 by mbentahi          #+#    #+#             */
/*   Updated: 2024/06/10 23:01:40 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void print_syntax_error(char *line)
{
	printf("syntax error near unexpected token `");
	printf("%s`\n",line);
}

t_element *skip_spaces(t_element *element,int dir)
{
	t_element *tmp;

	tmp = element;
	while (tmp && tmp->type == WHITESPACE)
	{
		if (dir == 1)
			tmp = tmp->next;
		else
			tmp = tmp->prev;		
	}
	return (tmp);
}

int is_redir(enum e_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT || type == APPEND || type == HERE_DOC)
		return (1);
	return (0);
}

int check_pipe(t_element *element)
{
	printf("check_pipe\n");
	t_element *next;
	t_element *prev;

	next = skip_spaces(element->next, 1);
	prev = skip_spaces(element->prev, -1);
	if (next->type == PIPE || prev->type == PIPE)
	{
		print_syntax_error("||");
		return (1);
	}
	else if (!prev || !next || is_redir(prev->type))
	{
		print_syntax_error("|");
		return (1);
	}
	return (0);
}

int check_redir(t_element *element)
{
	printf("check_redir\n");
	t_element *next;

	next = skip_spaces(element->next, 1);
	if (!next)
	{
		print_syntax_error("'newline'");
		return (1);
	}
	else if (is_redir(next->type))
	{
		print_syntax_error(next->line);
		return (1);
	}
	return (0);
}

int check_quotes(t_element **element, enum e_type type)
{
	while (*element)
	{
		*element = (*element)->next;
		if (!*element || (*element)->type == type)
			break;
	}
	if (!*element)
	{
		printf("quotes not closed\n");
		return (1);
	}
	return (0);
}

int check_syntax(t_element *element)
{
	printf("check_syntax\n");
	while (element)
	{
		if (element->type == PIPE)
		{
			if (check_pipe(element))
				return (1);
		}
		else if (is_redir(element->type))
		{
			if (check_redir(element))
				return (1);
		}
		else if (element->type == SQUOTE || element->type == DQUOTE)
		{
			if (check_quotes(&element, element->type))
				return (1);
		}
		element = element->next;
	}
	return (0);
}
