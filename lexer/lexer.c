/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:39:01 by mbentahi          #+#    #+#             */
/*   Updated: 2024/05/29 21:51:13 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int is_special(char c)
{
	if (c == '|' || c == '<' || c == '>' || ft_is_space(c) ||
	 c == '\n' || c == '\'' || c == '\"' || c == '$')
		return (1);
	return (0);
}

int get_word(char *line, t_element *element, enum e_state state)
{
	int i;

	i = 0;
	while (line[i] && !is_special(line[i]))
		i++;
	add_element(&element, new_element(line, i, WORD, state));
	return (i);
}

int tokenize(char *line, t_element *element, int i,enum e_state *state)
{
	if (!is_special(line[i]))
		i += get_word(line, element , *state);
	else if (line[i] == '|')
	{
		add_element(&element, new_element(line, i, PIPE, *state));
		i++;
	}
	else if (ft_is_space(line[i]))
	{
		add_element(&element, new_element(line, i, WHITESPACE, *state));
		i++;
	}
	else if (line[i] == '\n')
	{
		add_element(&element, new_element(line, i, NEW_LINE, *state));
		i++;
	}
	
	
	
}

t_element *lexing(char *line)
{
	t_element *element;
	enum e_state state;
	int i;

	i = 0;
	state = GENERAL;
	element = NULL;
	while (line[i])
	{
		
	}
}