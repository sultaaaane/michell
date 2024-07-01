NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
SRC =	lexer/lexer.c \
		main.c  \
		lexer/element_lst.c \
		syntax_error/syntax_error.c \
		parsing/parse.c \
		parsing/env.c \
		parsing/ft_strjoin_concate.c \

OBJ = $(SRC:.c=.o)

all: $(NAME) 

$(NAME):$(OBJ)
	@make -C libft
	$(CC) $(SRC) $(CFLAGS) -lreadline ./libft/libft.a -o $(NAME)


clean:
	rm -rf $(OBJ)
	@make clean -C libft
fclean: clean
	rm -rf $(NAME)
	@make fclean -C libft
re: fclean all
.SECONDARY: $(OBJ)