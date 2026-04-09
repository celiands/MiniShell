/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:17:22 by ngauthre          #+#    #+#             */
/*   Updated: 2025/08/13 10:50:53 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "built-in/builtin.h"
# include "parsing/parsing.h"
# include <sys/types.h>
# include <sys/wait.h>
# include "pipex/pipex.h"
# include <signal.h>

# define ERROR_CODE	127

extern int	g_sigstatus;

//pour les test
void	print_command_list(t_commands *list);

int		processing(t_commands *list, char ***env);
void	execute(t_commands *cmd, char **env);
int		*g_err_code(void);
void	siginit_minishell(void);
int		init_minishell(char ***env, char **argv, int argc);
void	set_err_code(int i);
size_t	size_commands(t_commands *list);
bool	check_no_cmd(const char *str);
void	loop_minishell(char **env);

int		max(int x, int y);

//sig
void	sigint_handler(int code);
void	sig_handler(int code);
void	sigquit_handler(int code);
void	sigint_heredoc(int code);

pid_t	*pid_handler(pid_t *value, int mod);

#endif