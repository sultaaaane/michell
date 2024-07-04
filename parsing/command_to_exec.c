/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:24:21 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/04 22:54:17 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

char **join_commad(t_element *element)
{
	char **command;
	t_element *tmp;
	int i;

	i = 0;
	tmp = element;
	while (tmp && tmp->type == WORD || tmp->type == CONCATE)
	{
		if (tmp->type == WORD || tmp->type == CONCATE)
			i++;
		tmp = tmp->next;
	}
	command = malloc(sizeof(char *) * (i + 1));
	if (!command)
		return (NULL);
	i = 0;
	tmp = element;
	while (tmp && tmp->type == WORD || tmp->type == CONCATE)
	{
		if (tmp->type == WORD || tmp->type == CONCATE)
		{
			command[i] = ft_strdup(tmp->line);
			i++;
		}
		tmp = tmp->next;
	}
	command[i] = NULL;
	return (command);
}

t_parse *command_to_exec(t_element *element)
{
	t_parse *new;
	t_element *tmp;

	new = NULL;
	tmp = element;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == CONCATE)
		{
			
			
		}

		tmp = tmp->next;
	}
	
}