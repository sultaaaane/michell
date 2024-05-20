CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJEC = $(SRC:.c=.o)
AUTHOR	= mbentahi (sultane)

#=== Colors ===
NO_COLOR = \033[0m
GRAY = \033[0;1;3;90m
RED = \033[0;1;3;91m
GREEN = \033[0;1;3;92m
YELLOW = \033[0;1;3;33m
BLUE = \033[0;1;3;34m
MAGENTA = \033[35m
CYAN = \033[36m


SRC	=		 ft_printadd.c    \
			 ft_printf.c      \
			 ft_putchar.c     \
			 ft_putnbr_base.c \
			 ft_putnbr.c      \
			 ft_putstr.c      \
			 ft_putlong.c     \

NAME = libftprintf.a

all: header $(NAME)
	@printf "$(GREEN)\n- Your library is ready ✅🥳\n$(NO_COLOR)"

$(NAME): $(OBJEC)
	@$(CC) $(CFLAGS) -c $(SRC)
	@ar rc $(NAME) $(OBJEC)

clean: header
	@rm -rf $(OBJEC)
	@printf "$(BLUE)clean\t:\t\t\t$(GREEN)[✓]$(NO_COLOR)\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "$(BLUE)fclean\t:\t\t\t$(GREEN)[✓]$(NO_COLOR)\n\n"

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJEC)
header :
	
	@printf "$(RED)\n"
	@echo " ██▓███    ██▀███    ██▓   ███▄    █  ▄▄▄█████▓  █████▒"
	@echo "▓██░  ██ ▒ ▓██  ██ ▒▓██▒   ██ ▀█   █    ▓██▒  ▓▒▓██   ▒" 	
	@echo "▓██░ ██▓  ▒▓██ ▄█  ▒▒██▒  ▓██  ▀█ ██▒▒  ▓██░  ▒░▒████ ░" 
	@echo "▒██▄█▓▒   ▒▒██▀▀█▄   ░██░ ▓██▒  ▐▌██▒░  ▓██▓  ░ ░▓█▒  ░"  
	@echo "▒██▒ ░   ░░██▓ ▒██▒ ░██░ ▒██░   ▓██░   ▒██▒  ░ ░▒█░   "    
	@echo "▒▓▒░ ░   ░░ ▒▓ ░▒▓░░ ▓   ░ ▒░   ▒ ▒    ▒ ░░     ▒ ░   "     
	@echo "░▒ ░        ░▒ ░ ▒░  ▒ ░ ░ ░░   ░ ▒░     ░     ░      "  
	@echo "░░          ░░   ░   ▒ ░   ░   ░ ░   ░       ░ ░      "
	@echo "             ░       ░           ░                    \n"              
	@printf  "$(MAGENTA)Author\t: $(GREEN)$(AUTHOR)\n"
	@printf  "$(MAGENTA)CC    \t: $(GREEN)$(CC)\n"
	@printf  "$(MAGENTA)Flags \t: $(GREEN)$(CFLAGS)\n$(CYAN)\n\n"