NAME = Minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
SRC =	lexer/lexer.c \
		lexer/main.c  \
		lexer/element_lst.c \
		syntax_error/syntax_error.c \

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