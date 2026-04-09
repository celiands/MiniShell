/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:16:38 by ngauthre          #+#    #+#             */
/*   Updated: 2025/08/13 10:50:19 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/libft.h"
# include <stdlib.h>
# include "../parsing/parsing.h"
# include "../minishell.h"
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

//built-in
int		unset(char **args, char ***env);
int		export(char **args, char ***env);
char	*get_evar(char *var, char **env);
void	print_env(char **arg, char **env, int fd);
int		set_evar(char *var, char *value, char **env);
int		change_dir(char **path, char ***env);
int		builtin_exit(t_commands *list, char **env);
int		echo(char **prompt, int fd);
int		pwd(char **args, int fd);
int		export_core(char *var, char ***env);
char	*err_code(void);

//utils
size_t	evs(const char *str);
size_t	env_size(char **env);
int		fsis(const char *big, const char *little, size_t len);
void	free_env(char **env);

//libft
char	*ft_strdup2(char *s);
size_t	ft_strlen2(const char *s);
char	*ft_strchr2(const char *s, int c);
size_t	ft_strlcpy2(char *dst, const char *src, size_t n);
char	*ft_strjoin2(char const *s1, char const *s2);
int		ft_atoi2(const char *s);
int		ft_isdigit2(int c);
void	ft_putstr_fd2(char *s, int fd);
int		ft_isalnum2(int c);

#endif