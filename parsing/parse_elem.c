/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:09:30 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/06 15:28:33 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_parse *new_parse(char **command,int fd_in, int fd_out)
{
	t_parse *parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (NULL);
	parse->full_command = command;
	parse->fd_in = fd_in;
	parse->fd_out = fd_out;
	parse->next = NULL;
	parse->prev = NULL;
	return (parse);
}

t_parse *add_parse(t_parse **lst, t_parse *parse)
{
	t_parse	*tmp;

	if (!*lst)
	{
		*lst = parse;
		return (parse);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = parse;
	parse->prev = tmp;
	return (parse);
}

void	free_parse(t_parse *lst)
{
	t_parse	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_free2d(lst->full_command);
		free(lst);
		lst = tmp;
	}
}

void print_parse(t_parse *lst)
{
	t_parse *tmp;
	int i;

	tmp = lst;
	while (tmp)
	{
		i = 0;
		while (tmp->full_command[i])
		{
			printf("command[%d] %s\n",i,tmp->full_command[i]);
			i++;
		}
			printf("fd_in %d\n",tmp->fd_in);
			printf("fd_out %d\n",tmp->fd_out);
		tmp = tmp->next;
	}
}
