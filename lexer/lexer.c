/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:39:01 by mbentahi          #+#    #+#             */
/*   Updated: 2024/05/30 18:23:40 by mbentahi         ###   ########.fr       */
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

void get_quote(t_element *element,char *line,enum e_state *state)
{
	enum e_state n_state;
	enum e_type type;

	if (*line == '\'')
	{
		n_state = IN_QUOTE;
		type = SQUOTE;
	}
	else if (*line == '\"')
	{
		n_state = IN_DQUOTE;
		type = DQUOTE;
	}
	if (*state == GENERAL)
	{
		add_element(&element, new_element(line, 1, type, *state));
		*state = n_state;
	}
	else if (*state == n_state)
	{
		*state = GENERAL;
		add_element(&element, new_element(line, 1, type, *state));
	}
	else
		add_element(&element, new_element(line, 1, type, *state));
}

int get_redirect(t_element *element, char *line, int i ,enum e_state *state)
{
	int j;

	j = i;
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			add_element(&element, new_element(line + i++, 2, HERE_DOC, *state));
		else
			add_element(&element, new_element(line + i, 1, REDIR_IN, *state));
		i++;
	}else if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			add_element(&element, new_element(line + i++, 2, APPEND, *state));
		else
			add_element(&element, new_element(line + i, 1, REDIR_OUT, *state));
		i++;
	}
	return (i - j);
}

int tokenize(char *line, t_element *element, int i,enum e_state *state)
{
	if (!is_special(line[i]))
		i += get_word(line + i, element , *state);
	else if (line[i] == '|')
		add_element(&element, new_element(line + i++, 1, PIPE, *state));
	else if (ft_is_space(line[i]))
		add_element(&element, new_element(line + i++, 1, WHITESPACE, *state));
	else if (line[i] == '\n')
		add_element(&element, new_element(line + i++, 1, NEW_LINE, *state));
	else if (line[i] == '\'' || line[i] == '\"')
		get_quote(element, line + i++, state);
	else if (line[i] == '<' || line[i ] == '>')
		i += get_redirect(element, line, i, state);
	else if (line[i] == '$')
	{
		add_element(&element, new_element(line, i, ENV, *state));
		i++;
	}
	return (i);
}

t_element	*init_elem(t_element *elem)
{
	elem = ft_calloc(1, sizeof(t_element));
	if (!elem)
		return (NULL);
	return (elem);
}

t_element *lexing(char *line)
{
	t_element *element;
	enum e_state state;
	int i;

	i = 0;
	state = GENERAL;
	element = NULL;
	element = init_elem(element);
	while (line[i])
		i = tokenize(line, element, i, &state);
	print_lst(element);
	return (element);
}