# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 16:03:00 by ngauthre          #+#    #+#              #
#    Updated: 2025/06/17 16:03:00 by ngauthre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Flags = -Wall -Werror -Wextra -g
OBJPATH = src/obj
src = src/built-in_utils1.c \
		src/cd.c \
		src/echo.c \
		src/env.c \
		src/export.c \
		src/get_evar.c \
		src/set_evar.c \
		src/unset.c \
		src/exit.c \
		src/pwd.c \
		src/fts_libft_1.c \
		src/fts_libft_2.c \
		src/exitcode.c 

obj = $(src:src/%.c=$(OBJPATH)/%.o)
NAME = built-in.a
CC = cc

RED	= \033[0;31m
GREEN = \033[0;32m
BLUE  = \033[0;34m
ORANGE = \033[1;33m
RESET = \033[0m
WHITE = \033[0m

all : $(NAME)

$(NAME) : $(obj)
	@echo "$(GREEN) ❈ Compilating $(NAME)...$(RESET)" 
	@ar rcs $(NAME)  $(obj) && \
	echo "$(ORANGE) ► $@ has been compiled ✔$(RESET)" || \
	(echo "$(RED) Failed : $@ $(RESET)" && exit 1)


$(OBJPATH)/%.o : src/%.c builtin.h
	@mkdir -p src/obj
	@$(CC) $(Flags) -c $< -o $@ -I . && \
	echo "$(BLUE)  ╰┈➤ $@ : Compiled ✔$(RESET)" || \
	(echo "$(RED) Failed : $@ $(RESET)" && exit 1)
	
clean :
	@echo "$(ORANGE) Cleaning $(NAME) in progress... $(WHITE)" 
	@rm -f $(obj)
	@echo "$(GREEN) Cleaning $(NAME) ✔ $(WHITE)" 

fclean : clean
	@rm -rf $(NAME)
	@echo "$(ORANGE)  ╰┈➤ $(NAME) : removed ✔$(WHITE)"

re : fclean all

.PHONY: all re clean fclean