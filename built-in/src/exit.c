/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:11:00 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/24 17:44:56 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_arg(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isdigit2((int)str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	sizeargv(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}

void	exit_core(char *err, char code, t_commands *list, char **env)
{
	if (err)
		ft_putstr_fd2(err, 2);
	free_command_list(list);
	free_env(env);
	rl_clear_history();
	ft_putstr_fd("exit\n", 1);
	exit(code);
}

int	builtin_exit(t_commands *list, char **env)
{
	if (!list || sizeargv(list->arg) == 1)
		return (exit_core(NULL, ft_atoi2(get_evar("?", env)), list, env), 0);
	if (check_arg(list->arg[1]) != 0)
		return (exit_core("Error : numeric arg required\n",
				(char)2, list, env), 0);
	if (sizeargv(list->arg) > 2)
		return (ft_putstr_fd("Error : Too many args\n", 2), 1);
	if (sizeargv(list->arg) == 2)
		return (exit_core(NULL, ft_atoi2(*(list->arg + 1)), list, env), 0);
	return (0);
}
