NAME = pipex
BNAME = checker
CC = cc

SRC = 	


OBJ = $(SRC:.c=.o)

all: $(NAME) 

$(NAME):$(OBJ)
	@make -C libft
	@make -C ft_printf
	$(CC) $(SRC) -Wall -Wextra -Werror -fsanitize=address -g3 ./ft_printf/libftprintf.a ./libft/libft.a -o $(NAME)


clean:
	rm -rf $(OBJ)
	@make clean -C libft
	@make clean -C ft_printf
fclean: clean
	rm -rf $(NAME)
	@make fclean -C libft
	@make fclean -C ft_printf
re: fclean all
.SECONDARY: $(OBJ)