/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:21:06 by ngauthre          #+#    #+#             */
/*   Updated: 2025/08/13 12:29:39 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../minishell.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <sys/stat.h>

extern int	g_sigstatus;

char		**ft_split(char const *s, char c);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*f_join(char const *s1, char sep, char const *s2);
char		**find_paths(char **envp);
char		*find_cmd(char **cmd, char **env);
void		unlimited_free_works(char **split);
void		free_pipes(int ***fds, int nb);
int			**create_pipes(int nb);
void		choose_out(t_commands *cmd, int **fds, int current);
int			****g_addr_pipes(void);
int			*g_max_nb(void);
void		choose_in(t_commands *cmd, int **fds, int current);
void		print_error(char *s, int i);
int			child_init(t_commands *cmd, char **env, int **fd, int id);
void		print_error(char *s, int i);

void		close_all(int **fds, int start);
void		end_pipe(int code, t_commands *cmd, char **env, char *path);
int			maxp(int x, int y);

//sep
void		pipex_core(t_commands *list, char **env, int **fds, int nb);
void		close_pipe(int	**fd, int id);
void		sig_init_p(void);
void		free_p(t_commands *list, char **env);

void		redir_child1(t_commands *cmd, int **fd, int i);
void		redir_child2(t_commands *cmd, int **fds, int i);

// minishell
int			pipex(t_commands *list, char **env);
size_t		size_commands_p(t_commands *list);
t_commands	*get_index(t_commands *list, int i);
int			execute_(t_commands *cmd, char *path, char ***env);
int			execute_builtin(t_commands *list, char ***env);
#endif