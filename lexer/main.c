/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:49:36 by mbentahi          #+#    #+#             */
/*   Updated: 2024/05/30 15:49:13 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"



int read_line(char **line)
{
	*line = readline("Mischell :?>");
	if (!*line  || ft_strcmp(*line, "exit") == 0) //TODO
	{
		printf("exit\n");
		free(*line);
		exit(1);
	}
	if (ft_strlen(*line) > 0)
		add_history(*line);
	if (ft_strlen(*line) == 0 || ft_is_whitespace(*line))
	{
		free(*line);
		return (1);
	}
	return (0);
}

void sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int main()
{
	char *line;
	t_element *element;
	line = NULL;
	signal(SIGQUIT, SIG_IGN);
	while (69)
	{
		signal(SIGINT, sig_handler);
		if (read_line(&line))
			continue;
		element = lexing(line);
		free(line);
	}	
}