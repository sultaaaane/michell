/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:49:36 by mbentahi          #+#    #+#             */
/*   Updated: 2024/06/11 03:15:14 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"

int read_line(char **line)
{
	*line = readline("Mischell :?>");
	if (!*line  || ft_strcmp(*line, "exit") == 0)
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




int main(int ac, char **av, char **envp)
{
	char *line;
	t_all all;
	t_env *envlist;

	(void)ac;
	(void)av;
	envlist = NULL;
	all = (t_all){0};
	all.env = envp;
	line = NULL;
	signal(SIGQUIT, SIG_IGN);
	envlist = build_env_list(envp);
	while (69)
	{
		signal(SIGINT, sig_handler);
		if (read_line(&line))
			continue;
		all.element = lexing(line, &envlist);
		if (!check_syntax(all.element))
		{
			print_lst(all.element);
			printf("proceed to execution\n");
		}
		free(line);
	}	
}