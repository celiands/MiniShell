# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 12:07:20 by cde-bard          #+#    #+#              #
#    Updated: 2025/06/17 23:41:58 by ngauthre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
C = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_printf.c ft_print_scdiu.c ft_print_pxX.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c get_next_line.c get_next_line_utils.c
O = $(foreach o, $(C:.c=.o), tmp/$(o))

FLAGS = -Wall -Werror -Wextra -g

GREEN = \033[1;32m
ORANGE = \033[1;33m
BLUE  = \033[0;34m
RED	= \033[0;31m
WHITE = \033[0m

all : $(NAME)

$(NAME) : tmp $(O)
	@echo "$(GREEN) ❈ Compilating $(NAME)...$(WHITE)"
	@ar rcs $(NAME) $(O)
	
tmp/%.o : %.c libft.h
	@cc -o $@ $(FLAGS) -c $< -I .  && \
	echo "$(BLUE)╰┈➤ $@ : Compiled ✔$(WHITE)" || \
	(echo "$(RED) Failed : $@ $(WHITE)" && exit 1)

tmp :
	@mkdir -p tmp

clean :
	@echo "$(ORANGE) Cleaning $(NAME) in progress... $(WHITE)" 
	@rm -f $(O)
	@echo "$(GREEN) Cleaning $(NAME) ✔ $(WHITE)" 

fclean : clean
	@rm -f $(NAME)
	@echo "$(ORANGE)  ╰┈➤ $(NAME) : removed ✔$(WHITE)"

re : fclean all

bonus : all

main : bonus
	cc -Wall -Werror -Wextra main.c $(NAME)
	@echo "$(GREEN)./a.out\n"
	@valgrind ./a.out

mclean : fclean
	rm -f a.out
	@echo "$(BLUE)"
	@ls