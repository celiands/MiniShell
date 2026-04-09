/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:42:02 by cde-bard          #+#    #+#             */
/*   Updated: 2025/08/13 11:53:55 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <signal.h>

typedef struct s_commands
{
	char				**arg;
	int					fd_infile;
	int					fd_outfile;
	bool				stop_pars;
	struct s_commands	*next;
}						t_commands;

bool		syntax_error(char **split);
char		*get_evar(char *var, char **env);
void		set_err_code(int i);
bool		is_meta(char c);
bool		expand_in(char *input, char *expanded_input, char **env);
char		*var_name(char *start);
t_commands	*parse_in_list(char **split, char **env);
t_commands	*last_command(t_commands *list);
void		free_command_list(t_commands *list);
bool		parse_command(char **split, t_commands *command, int *i,
				char **env);
void		free_tab(char **tab);
t_commands	*parse_user_input(char *user_input, char **env);
bool		is_pipe(char *node);
bool		is_redir(char *n);
bool		is_whitespace(char c);
char		*heredoc_expand(char *user_input, char **env);
bool		expand_dolar(char **input, char **expanded_input, char **env,
				char sep);
int			sizemax_user_input(char *user_input, char **env);
bool		check_unclosed_quotes(char *user_input);

//norm
void		init_sizemax_user_input(int *i, int *size);
void		heredoc_norm_close(int *fd_dup);
void		expand_char(char **input, char **expanded_input, char c);

#endif
