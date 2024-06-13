/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:39:01 by mbentahi          #+#    #+#             */
/*   Updated: 2024/06/12 16:43:10 by mbentahi         ###   ########.fr       */
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

int get_word(char *line, t_element **element, enum e_state state)
{
	int i;

	i = 0;
	while (line[i] && !is_special(line[i]))
		i++;
	add_element(element, new_element(line, i, WORD, state));
	return (i);
}

void get_quote(t_element **element,char *line,enum e_state *state)
{
	enum e_state n_state;
	enum e_type type;

	if (*line == '\'')
	{
		n_state = IN_SQUOTE;
		type = SQUOTE;
	}
	else if (*line == '\"')
	{
		n_state = IN_DQUOTE;
		type = DQUOTE;
	}
	if (*state == GENERAL)
	{
		add_element(element, new_element(line, 1, type, *state));
		*state = n_state;
	}
	else if (*state == n_state)
	{
		*state = GENERAL;
		add_element(element, new_element(line, 1, type, *state));
	}
	else
		add_element(element, new_element(line, 1, type, *state));
}

int get_redirect(t_element **element, char *line, int i ,enum e_state *state)
{
	int j;

	j = i;
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			add_element(element, new_element(line + i++, 2, HERE_DOC, *state));
		else
			add_element(element, new_element(line + i, 1, REDIR_IN, *state));
		i++;
	}else if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			add_element(element, new_element(line + i++, 2, APPEND, *state));
		else
			add_element(element, new_element(line + i, 1, REDIR_OUT, *state));
		i++;
	}
	return (i - j);
}

void	check_prev_node(t_element *current)
{
	t_element *tmp = current;
	if (current->prev)
	{
		while(current && current->type != WHITESPACE && current->type != HERE_DOC)
			current = current->prev;
		if(current)
		current = skip_spaces(current, -1);
		if (current && current->type == HERE_DOC)
			tmp->type = WORD;
	}
}

int get_env(char *line, t_element **element, enum e_state state)
{
	enum e_type type1;
	enum e_type type2;
	int i;

	i = 1;
	if (state == IN_SQUOTE)
	{
		type1 = WORD;
		type2 = WORD;
	}
	else
	{
		type1 = ENV;
		type2 = EX_STATUS;
	}
	if (line[i] == '?')
		add_element(element, new_element(line, ++i, type2, state));
	else
	{
		while (line[i] && !is_special(line[i]))
			i++;
		add_element(element, new_element(line, i, type1, state));
	}
	return (i);
}

int tokenize(char *line, t_element **element, int i,enum e_state *state)
{
	if (!is_special(line[i]))
		i += get_word(line + i, element , *state);
	else if (line[i] == '|')
		add_element(element, new_element(line + i++, 1, PIPE, *state));
	else if (ft_is_space(line[i]))
		add_element(element, new_element(line + i++, 1, WHITESPACE, *state));
	else if (line[i] == '\n')
		add_element(element, new_element(line + i++, 1, NEW_LINE, *state));
	else if (line[i] == '\'' || line[i] == '\"')
		get_quote(element, line + i++, state);
	else if (line[i] == '<' || line[i ] == '>')
		i += get_redirect(element, line, i, state);
	else if (line[i] == '$')
		i += get_env(line + i, element, *state);
	return (i);
}

t_element	*init_elem(t_element *elem)
{
	elem = ft_calloc(1, sizeof(t_element));
	if (!elem)
		return (NULL);
	return (elem);
}

void	check(t_element *current)
{
	while(current)
	{
		if(current->type == ENV)
		{	
			check_prev_node(current);
		}
		current = current->next;
	}
}

void expand_helper(t_element *current, t_env **envlist, t_element **new)
{
	t_env *env = *envlist;
	char **arr;
	int i = 0;

	while (env)
	{
		if (ft_strcmp(current->line + 1, env->key) == 0)
		{
			if(env->value)
			{
				if(current->state == 0)
				{
					arr = ft_split(env->value, ' ');
					if(arr)
					{
						while (arr[i])
						{
							add_element(new, new_element(arr[i], ft_strlen(arr[i]), current->type, current->state));
							i++;
						}
						ft_free2d(arr);
					}
				}
				else
					add_element(new, new_element(env->value, ft_strlen(env->value), current->type, current->state));
			}
			else
				add_element(new, new_element("", 0, current->type, current->state));
			break;
		}
		env = env->next;
	}
}

t_element *expand(t_element *current, t_env **envlist)
{
	t_env *tmp;
	t_env *head;
	t_element *new = NULL;

	head = *envlist;
	while (current)
	{
		if (current->type == ENV)
		{
			tmp = head;
			expand_helper(current, envlist, &new);
		}
		else
			add_element(&new, new_element(current->line, ft_strlen(current->line), current->type, current->state));
		current = current->next;
	}
	return (new);
}

t_element *lexing(char *line, t_env **envlist)
{
	t_element *element;
	enum e_state state;
	int i;

	i = 0;
	state = GENERAL;
	element = NULL;
	while (line[i])
		i = tokenize(line, &element, i, &state);
	check(element);
	element = expand(element, envlist);
	check_concate(&element);
	return (element);
}