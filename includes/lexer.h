/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:49:02 by mbentahi          #+#    #+#             */
/*   Updated: 2024/06/30 19:41:52 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef enum e_type
{
	WORD,
	SQUOTE,
	DQUOTE,
	PIPE,
	WHITESPACE = ' ',
	OUTPUT,
	HERE_DOC,
	APPEND,
	REDIR_IN,
	REDIR_OUT,
	ENV,
	NEW_LINE,
	EX_STATUS,
	CONCATE,
} t_type;

typedef enum e_state
{
	GENERAL,
	IN_SQUOTE,
	IN_DQUOTE,
}t_state;

typedef struct s_lexer
{
	char	*input;
	int		size;
	int		index;
}t_lexer;
typedef struct s_element
{
	char *line;
	t_state state;
	t_type type;
	struct s_element *next;
	struct s_element *prev;
}t_element;

typedef struct s_parse
{
	int *fd_in;
	int *fd_out;
	char *cmd;
	char **full_command;
	struct s_parse *next;
	struct s_parse *prev;
}t_parse;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}               t_env;

typedef struct s_all
{
	t_element *element;
	t_parse *parse;
	t_list *lst;
	char **env;
	int in;
	int out;
}t_all;


void	print_lst(t_element *lst);
void	free_lst(t_element *lst);
void	add_element(t_element **lst, t_element *element);
t_element	*new_element(char *line, int i,enum e_type type, enum e_state state);
int get_word(char *line, t_element **element, enum e_state state);
int is_special(char c);
int tokenize(char *line, t_element **element, int i,enum e_state *state);
t_element *lexing(char *line);
int get_redirect(t_element **element, char *line, int i ,enum e_state *state);
void get_quote(t_element **element,char *line,enum e_state *state);
int get_word(char *line, t_element **element, enum e_state state);
void print_syntax_error(char *line);
t_element *skip_spaces(t_element *element,int dir);
int check_syntax(t_element *element);
int check_quotes(t_element **element, enum e_type type);
int check_redir(t_element *element);
int check_pipe(t_element *element);
int is_redir(enum e_type type);
void print_syntax_error(char *line);
void print_parse(t_parse *lst);
void	free_parse(t_parse *lst);
t_parse *add_parse(t_parse **lst, t_parse *parse);
t_parse *new_parse(char **command,int fd_in, int fd_out);
int parse(t_element *element);
t_element	*check_concate(t_element **element);
int count_nodes(t_element *curr);
t_env *create_env_node(char *key, char *value);
t_env *build_env_list(char **envp);
void add_element_between(t_element **lst, t_element *element, t_element *prev, t_element *next);
t_element *without_quotes(t_element *element);
t_element *expand(t_element *current, t_env **envlist);
void	check(t_element *current);
t_element *join_inquotes(t_element *element);
char	*ft_strjoin_concate(char *s1, char *s2);




#endif