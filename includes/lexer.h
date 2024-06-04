/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:49:02 by mbentahi          #+#    #+#             */
/*   Updated: 2024/06/03 17:48:32 by mbentahi         ###   ########.fr       */
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
	WHITESPACE,
	OUTPUT,
	HERE_DOC,
	APPEND,
	REDIR_IN,
	REDIR_OUT,
	ENV,
	NEW_LINE,
	EX_STATUS,
} t_type;

typedef enum e_state
{
	IN_DQUOTE,
	IN_SQUOTE,
	GENERAL,
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
	int fd_in;
	int fd_out;
	char **full_command;
	
}t_parse;

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





#endif