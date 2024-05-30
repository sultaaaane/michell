/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:49:02 by mbentahi          #+#    #+#             */
/*   Updated: 2024/05/30 14:58:52 by mbentahi         ###   ########.fr       */
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
} t_type;

typedef enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
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

void	print_lst(t_element *lst);
void	free_lst(t_element *lst);
void	add_element(t_element **lst, t_element *element);
t_element	*new_element(char *line, int i,enum e_type type, enum e_state state);
int get_word(char *line, t_element *element, enum e_state state);
int is_special(char c);
int tokenize(char *line, t_element *element, int i,enum e_state *state);
t_element *lexing(char *line);
int get_redirect(t_element *element, char *line, int i ,enum e_state *state);
void get_quote(t_element *element,char *line,enum e_state *state);
int get_word(char *line, t_element *element, enum e_state state);













#endif