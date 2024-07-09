/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:49:36 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/09 13:08:51 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"

// char *handle_heredoc(char *delimiter)
// {
//     char *line;
//     char *content = ft_strdup("");
//     printf("delimiter: %s\n", delimiter);
//     while (1)
//     {
//         line = readline("> ");
//         if (!line || ft_strcmp(line, delimiter) == 0)
//         {
// 			printf("exit\n");
//             free(line);
//             break;
//         }
//         content = ft_strjoin(content, line);
//         content = ft_strjoin(content, "\n");
//         free(line);
//     }
//     return content;
// }

// t_element *handle_heredocs(t_element *element)
// {
// 	t_element *curr;
// 	t_element *tmp;
// 	char *content;
// 	char *delimiter;

// 	curr = element;
// 	while (curr)
// 	{
// 		if (curr->type == HERE_DOC)
// 		{
// 			delimiter = ft_strdup(curr->line);
// 			tmp = curr->next;
// 			content = handle_heredoc(delimiter);
// 			free(curr->line);
// 			curr->line = content;
// 			curr->type = WORD;
// 			curr->next = tmp;
// 			if (tmp)
// 				tmp->prev = curr;
// 		}
// 		curr = curr->next;
// 	}
// 	return element;
// }

// int read_line(char **line)
// {
// 	*line = readline("Mischell :?>");
// 	if (!*line  || ft_strcmp(*line, "exit") == 0)
// 	{
// 		printf("exit\n");
// 		free(*line);
// 		exit(1);
// 	}
// 	if (ft_strlen(*line) > 0)
// 		add_history(*line);
// 	if (ft_strlen(*line) == 0 || ft_is_whitespace(*line))
// 	{
// 		free(*line);
// 		return (1);
// 	}
// 	return (0);
// }

// void sig_handler(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

// int main(int ac, char **av, char **envp)
// {
// 	char *line;
// 	t_all all;
// 	t_element *tmp;
// 	t_env *envlist;
// 	t_parse *parse;

// 	(void)ac;
// 	(void)av;
// 	tmp = NULL;
// 	envlist = NULL;
// 	all = (t_all){0};
// 	all.env = envp;
// 	line = NULL;
// 	signal(SIGQUIT, SIG_IGN);
// 	envlist = build_env_list(envp);
// 	parse = NULL;
// 	while (69)
// 	{
// 		signal(SIGINT, sig_handler);
// 		if (read_line(&line))
// 			continue;
// 		all.element = lexing(line);
// 		if (!check_syntax(all.element))
// 		{
// 			check(all.element);
// 			end_of_file(&all.element);
// 			all.element = expand(all.element, &envlist);
// 			all.element = join_inquotes(all.element);
// 			tmp = without_quotes(all.element);
// 			tmp = check_concate(&tmp);
// 			print_lst(tmp);
// 			printf("proceed to execution\n");
// 		}
// 		free(line);
// 		free_lst(all.element);
// 	}
// 	ft_free2d(envp);
// }

#include <fcntl.h>
#define HEREDOC_TEMP "/tmp/heredoc_temp"

char *handle_heredoc(char *delimiter)
{
    char *line = NULL;
    char *content = ft_strdup("");
    char *temp;

    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        temp = ft_strjoin_concate(content, line);
        free(content);
        content = ft_strjoin_concate(temp, "\n");
        free(temp);
        free(line);
    }
    return content;
}

int read_line(char **line)
{
    *line = readline("Mischell :?>");
    if (!*line || ft_strcmp(*line, "exit") == 0)
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
    t_element *tmp;
    t_env *envlist;
    t_parse *parse;

    (void)ac;
    (void)av;
    tmp = NULL;
    envlist = NULL;
    all = (t_all){0};
    all.env = envp;
    line = NULL;
    signal(SIGQUIT, SIG_IGN);
    envlist = build_env_list(envp);
    parse = NULL;
    while (69)
    {
        signal(SIGINT, sig_handler);
        if (read_line(&line))
            continue;
        all.element = lexing(line);
        if (!check_syntax(all.element))
        {
            check(all.element);
            end_of_file(&all.element);
            
            t_element *current = all.element;
            while (current)
            {
                if (current->type == HERE_DOC && current->next)
                {
					current = current->next;
					current = skip_spaces(current, 1);
					printf("current->line: %s\n", current->line);
                    char *heredoc_content = handle_heredoc(current->line);
                    int fd = open(HEREDOC_TEMP, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd != -1)
                    {
                        write(fd, heredoc_content, ft_strlen(heredoc_content));
                        close(fd);
                    }
                    free(heredoc_content);
                }
                current = current->next;
            }
            free_lst(current);
            all.element = expand(all.element, &envlist);
            all.element = join_inquotes(all.element);
            tmp = without_quotes(all.element);
            tmp = check_concate(&tmp);
            print_lst(tmp);
            printf("proceed to execution\n");
        }
        free(line);
        free_lst(all.element);
		free_lst(tmp);
    }
    ft_free2d(envp);
}
