# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/15 13:38:41 by cde-bard          #+#    #+#              #
#    Updated: 2025/08/13 10:35:05 by ngauthre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parsing.a
C = parse_user_input.c expand.c norm_utils.c parse_in_list.c parse_command.c syntax_error.c expand_heredoc.c 
O2 = ../libft/tmp/ft_substr.o ../libft/tmp/ft_split.o ../libft/tmp/ft_putendl_fd.o  ../libft/tmp/ft_calloc.o ../libft/tmp/ft_putstr_fd.o ../libft/tmp/ft_bzero.o ../libft/tmp/ft_strncmp.o
O3 = ../built-in/src/obj/get_evar.o
O = $(foreach o, $(C:.c=.o), tmp/$(o)) $(O2) $(O3)

WFLAGS = -Wall -Wextra -Werror
LIBFT = ../libft/libft.a

GREEN = \033[1;32m
ORANGE = \033[0;33m
BLUE = \033[1;33m
WHITE = \033[0m
RED	= \033[0;31m
GREEN = \033[0;32m
BLUE  = \033[0;34m
ORANGE = \033[1;33m
RESET = \033[0m
WHITE = \033[0m

all : $(NAME)

$(NAME) : $(LIBFT) tmp $(O)
	@echo "$(GREEN)\nCompilating $(NAME)$(WHITE)"
	@ar rcs $(NAME) $(LIBFT) $(O) && \
	echo "$(ORANGE) ► $@ has been compiled ✔$(WHITE)" || \
	(echo "$(RED) Failed : $@ $(WHITE)" && exit 1)

tmp/%.o : %.c parsing.h
	@$(CC) $(Flags) -c $< -o $@ -I . && \
	echo "$(BLUE)  ╰┈➤ $@ : Compiled ✔$(WHITE)" || \
	(echo "$(RED) Failed : $@ $(WHITE)" && exit 1)

tmp :
	@mkdir tmp

$(LIBFT) :
	@make -C ../libft all
	@echo "\n"

clean :
	@rm -f $(O)

fclean : clean
	@rm -f $(NAME)

re : fclean all