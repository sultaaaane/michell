/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:24:21 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/05 17:02:59 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int count_command(t_element *element)
{
	int i;
	t_element *tmp;

	i = 0;
	tmp = element;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == CONCATE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char **join_command(t_element **element)
{
	char **command;
	t_element *tmp;
	int i;

	i = count_command(*element);
	printf("i = %d\n", i);
	command = malloc(sizeof(char *) * (i + 1));
	if (!command)
		return (NULL);
	i = 0;
	tmp = *element;
	while (tmp && (tmp->type == WORD || tmp->type == CONCATE))
	{
		command[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	command[i] = NULL;
	return (command);
}

t_parse *command_to_exec(t_element *element)
{
	t_parse *new;
	t_element *tmp;
	char **command;
	
	command = NULL;
	new = NULL;
	tmp = element;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == PIPE)
			tmp = tmp->next;
		command = join_command(&tmp);
		if (command)
		{
			new = add_parse(&new, new_parse(ft_strdup_2d(command), 0, 1));
			ft_free2d(command);
		}
		tmp = tmp->next;
	}
	return (new);
}
