# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/15 13:38:41 by cde-bard          #+#    #+#              #
#    Updated: 2025/08/13 12:21:02 by ngauthre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
C = src_minishell/minishell.c src_minishell/minishell_utils3.c src_minishell/execute_bash.c src_minishell/minishell_utils1.c src_minishell/signals.c src_minishell/minishell_utils2.c
O = $(C:src_minishell/%.c=tmp/%.o)

libBuilt-in = built-in/built-in.a
libparsing = parsing/parsing.a
libpipex = pipex/pipex.a
SRC_PARSING = parsing/parse_user_input.c parsing/expand.c parsing/parse_in_list.c parsing/parse_command.c parsing/norm_utils.c parsing/syntax_error.c parsing/expand_heredoc.c 
SRC_BUILT-IN = built-in/src/built-in_utils1.c built-in/src/cd.c built-in/src/echo.c built-in/src/env.c built-in/src/exit.c built-in/src/exitcode.c built-in/src/export.c built-in/src/fts_libft_1.c built-in/src/fts_libft_2.c built-in/src/get_evar.c built-in/src/pwd.c built-in/src/set_evar.c built-in/src/unset.c
SRC_PIPEX = pipex/pipex_multi_utils.c pipex/pipex_multi_utils2.c pipex/pipex_utils.c pipex/pipex_utils2.c pipex/pipex.c pipex/pipex_minishell_utils.c pipex/split.c
OBJ_BI = $(src:.c=.o)

WFLAGS = -Wall -Wextra -Werror -g
LIBFT = libft/libft.a

GREEN = \033[1;32m
ORANGE = \033[1;33m
BLUE  = \033[0;34m
RED	= \033[0;31m
WHITE = \033[0m

all : $(NAME)

$(NAME) : $(LIBFT) $(libBuilt-in) $(libparsing) $(libpipex) tmp $(O)
	@echo "$(GREEN) ❈ Compilating $(NAME)...$(WHITE)"
	@cc -o $(NAME) $(WFLAGS) $(O) $(LIBFT) $(libBuilt-in) $(libparsing) $(libpipex) -lreadline

tmp/%.o : src_minishell/%.c minishell.h
	@cc -o $@ $(WFLAGS) -c $< -I .  && \
	echo "$(BLUE) ➤ $@ : Compiled ✔$(WHITE)" || \
	(echo "$(RED) Failed : $@ $(WHITE)" && exit 1)

tmp :
	@mkdir tmp

$(LIBFT) :
	@echo "$(GREEN)\n ❈ Start Libft's compilation...$(WHITE)"
	@make --no-print-directory -C libft all

$(libBuilt-in) : $(SRC_BUILT-IN) built-in/builtin.h
	@echo "$(GREEN)\n ❈ Start Built-in's compilation...$(WHITE)"
	@make --no-print-directory -C built-in

$(libparsing) : $(SRC_PARSING)
	@echo "$(GREEN)\n ❈ Start Parsing's compilation...$(WHITE)"
	@make --no-print-directory -C parsing

$(libpipex) : $(SRC_PIPEX)
	@echo "$(GREEN)\n ❈ Start pipex's compilation...$(WHITE)"
	@make --no-print-directory -C pipex

clean :
	@echo "$(ORANGE) Cleaning $(NAME) in progress... $(WHITE)" 
	@rm -f $(O)
	@make --no-print-directory -C libft clean
	@make --no-print-directory -C built-in clean
	@make --no-print-directory -C parsing clean
	@make --no-print-directory -C pipex clean
	@echo "$(GREEN) Cleaning $(NAME) ✔ $(WHITE)" 

fclean : clean
	@make --no-print-directory -C libft fclean
	@make --no-print-directory -C built-in fclean
	@make --no-print-directory -C parsing fclean
	@make --no-print-directory -C pipex fclean
	@rm -f $(NAME)
	@echo "$(ORANGE)  ╰┈➤ $(NAME) : removed ✔$(WHITE)"

re : fclean all

.PHONY : all re clean fclean