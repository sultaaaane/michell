/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:49:36 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/10 22:11:53 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"
#define HEREDOC_TEMP "/tmp/heredoc_temp"

char *handle_heredoc(char *delimiter,t_element **heredoc, t_env **envlist,int flag)
{
    char *line = NULL;
    char *content = ft_strdup("");
    char *temp;

    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, delimiter) == 0)
        {
            *heredoc = lexing(content);
            if (flag)
                *heredoc = expand(*heredoc, envlist);
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

void write_element_intofile(t_element *element, int fd)
{
    while (element)
    {
        write(fd, element->line, ft_strlen(element->line));
        // write(fd, "\n", 1);
        element = element->next;
    }
}

void handle_env(t_element **current)
{
    t_element *tmp = *current;
    char *line = NULL;

    while (tmp)
    {
        if (tmp->type == ENV)
        {
            int i = 1;
            if (ft_keyboardup(tmp->line[i]) || ft_isdigit(tmp->line[i]))
                i++;
            else
                return;
            line = ft_strjoin(line, &tmp->line[i]);
            i++;
            free(tmp->line);
            tmp->line = ft_strdup(line);
            free(line);
        }
        tmp = tmp->next;
    }
}

int main(int ac, char **av, char **envp)
{
    char *line;
    t_all all;
    t_element *tmp;
    t_env *envlist;
    t_parse *parse;
    int flag = 1;

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
            handle_env(&all.element);
            all.element = expand(all.element, &envlist);
            printf("expand\n");
            print_lst(all.element);
            all.element = join_inquotes(all.element);
            printf("join_inquotes\n");
            print_lst(all.element);
            tmp = without_quotes(all.element);
            printf("without_quotes\n");
            print_lst(tmp);
            tmp = check_concate(&tmp);
            printf("check_concate\n");
            
            t_element *current = all.element;
            t_element *tmp1 = NULL;
            while (current)
            {
                if (current->type == HERE_DOC && current->next)
                {
                    
					current = current->next;
					current = skip_spaces(current, 1);
                    if (current->state == IN_SQUOTE || current->state == IN_DQUOTE)
                        flag = 0;
                    
					printf("current->line: %s\n", current->line);
                    char *heredoc_content = handle_heredoc(current->line, &tmp1, &envlist, flag);
                    int fd = open(HEREDOC_TEMP, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd != -1)
                    {
                        write_element_intofile(tmp1, fd);
                        close(fd);
                        fd = open(HEREDOC_TEMP, O_RDONLY);
                    }
                    free(heredoc_content);
                }
                current = current->next;
            }
            free_lst(current);
            free_lst(tmp1);
            print_lst(tmp);
            printf("proceed to execution\n");
        }
        free(line);
        free_lst(all.element);
		free_lst(tmp);
    }
    ft_free2d(envp);
}
