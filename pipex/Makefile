# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cde-bard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/14 10:56:24 by cde-bard          #+#    #+#              #
#    Updated: 2025/08/14 10:56:29 by cde-bard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a
FLAGS = -Wall -Werror -Wextra -g
SRC_LIBFT = ../libft/ft_strlen.c ../libft/ ../libft/
SRC = pipex_multi_utils.c \
	pipex_multi_utils2.c \
	pipex_utils.c \
	pipex_utils2.c \
	pipex.c \
	pipex_minishell_utils.c \
	split.c
OBJ_BUILTIN = ../built-in/src/obj/built-in_utils1.o \
			../built-in/src/obj/cd.o \
			../built-in/src/obj/echo.o \
			../built-in/src/obj/env.o \
			../built-in/src/obj/exit.o \
			../built-in/src/obj/exitcode.o \
			../built-in/src/obj/export.o \
			../built-in/src/obj/fts_libft_1.o \
			../built-in/src/obj/fts_libft_2.o \
			../built-in/src/obj/get_evar.o \
			../built-in/src/obj/pwd.o \
			../built-in/src/obj/set_evar.o \
			../built-in/src/obj/unset.o

OBJ = $(foreach o, $(SRC:.c=.o), obj/$(o)) $(OBJ_BUILTIN)
HEADERS = pipex.h

#couleurs
RED	= \033[0;31m
GREEN = \033[0;32m
BLUE  = \033[0;34m
YELLOW = \033[1;33m
RESET = \033[0m

all : $(NAME)

$(NAME) : obj $(OBJ)
	@echo "$(GREEN) Compilation in progress...$(RESET)" 
	@ar rcs $(NAME) $(OBJ) $(OBJ_BUILTIN)
	@echo "$(YELLOW) $@ has been compiled ✔$(RESET)" 

obj/%.o : %.c pipex.h
	@$(CC) $(FLAGS) -c $< -o $@ -I . && \
	echo "$(BLUE) $@ : Compiled ✔$(RESET)" || \
	(echo "$(RED) Failed : $@ $(RESET)" && exit 1)

obj :
	@mkdir -p obj

clean :
	@echo "$(GREEN) Cleaning in progress... $(RESET)" 
	@rm -f $(OBJ)
	@echo "$(GREEN) Cleaning ✔ $(RESET)" 

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY: all re clean fclean
