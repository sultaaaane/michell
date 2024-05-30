CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJEC = $(SRC:.c=.o)
BOBJEC = $(BONUS:.c=.o)
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


SRC	=		 ft_strlen.c \
			 ft_memmove.c \
			 ft_memcpy.c \
			 ft_strlcpy.c \
			 ft_strlcat.c \
			 ft_isalpha.c \
			 ft_isdigit.c \
			 ft_isalnum.c \
			 ft_isascii.c \
			 ft_isprint.c \
			 ft_memset.c \
			 ft_bzero.c \
			 ft_toupper.c \
			 ft_tolower.c \
			 ft_strchr.c \
			 ft_strrchr.c \
			 ft_strncmp.c \
			 ft_atoi.c \
			 ft_calloc.c \
			 ft_strdup.c \
			 ft_strnstr.c \
			 ft_memchr.c \
			 ft_memcmp.c \
			 ft_substr.c \
			 ft_strjoin.c \
			 ft_putchar_fd.c \
			 ft_putendl_fd.c \
			 ft_putstr_fd.c \
			 ft_putnbr_fd.c \
			 ft_strtrim.c \
			 ft_strmapi.c \
			 ft_split.c \
			 ft_striteri.c \
			 ft_itoa.c \
			 ft_lstadd_back_bonus.c \
			 ft_lstadd_front_bonus.c \
			 ft_lstnew_bonus.c \
			 ft_lstsize_bonus.c \
			 ft_lstlast_bonus.c \
			 ft_lstdelone_bonus.c \
			 ft_lstclear_bonus.c \
			 ft_lstiter_bonus.c \
			 ft_lstmap_bonus.c \
			 get_next_line.c \
			 ft_free2d.c \
			 ft_is_whitespace.c \

BONUS = 	 ft_lstadd_back_bonus.c \
			 ft_lstadd_front_bonus.c \
			 ft_lstnew_bonus.c \
			 ft_lstsize_bonus.c \
			 ft_lstlast_bonus.c \
			 ft_lstdelone_bonus.c \
			 ft_lstclear_bonus.c \
			 ft_lstiter_bonus.c \
			 ft_lstmap_bonus.c \

NAME = libft.a

all: header $(NAME)
	@printf "$(GREEN)\n- Your library is ready ✅🥳\n$(NO_COLOR)"

$(NAME): $(OBJEC)
	@$(CC) $(CFLAGS) -c $(SRC)
	@ar rc $(NAME) $(OBJEC)

$(BOBJEC): $(BONUS)
	@$(CC) $(CFLAGS) -c $(BONUS)
	@ar rc $(NAME) $(BOBJEC)

bonus: header $(BOBJEC)
	@printf "$(GREEN)\n- Your bonus library is ready ✅🥳\n$(NO_COLOR)"

clean: header
	@rm -rf $(BOBJEC) $(OBJEC)
	@printf "$(BLUE)clean\t:\t\t\t$(GREEN)[✓]$(NO_COLOR)\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "$(BLUE)fclean\t:\t\t\t$(GREEN)[✓]$(NO_COLOR)\n\n"

re: fclean all

.PHONY: all clean fclean bonus re
.SECONDARY: $(OBJEC) $(BOBJEC)
header :

	@printf "$(RED)"
	@echo "██▓     ██▓ ▄▄▄▄     █████▒▄▄▄█████▓"
	@echo "▓██▒    ▓██▒▓█████▄ ▓██   ▒ ▓  ██▒ ▓▒"
	@echo "▒██░    ▒██▒▒██▒ ▄██▒████ ░ ▒ ▓██░ ▒░"
	@echo "▒██░    ░██░▒██░█▀  ░▓█▒  ░ ░ ▓██▓ ░"
	@echo "░██████▒░██░░▓█  ▀█▓░▒█░      ▒██▒ ░" 
	@echo "░ ▒░▓  ░░▓  ░▒▓███▀▒ ▒ ░      ▒ ░░"   
	@echo "░ ░ ▒  ░ ▒ ░▒░▒   ░  ░          ░"    
	@echo "  ░ ░    ▒ ░ ░    ░  ░ ░      ░"      
	@echo "    ░  ░ ░   ░"                       
	@echo "                  ░"                  
	@printf  "$(MAGENTA)Author\t: $(GRAY)$(AUTHOR)\n"
	@printf  "$(MAGENTA)CC    \t: $(CYAN)$(CC)\n"
	@printf  "$(MAGENTA)Flags \t: $(CYAN)$(CFLAGS)\n"
