/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_multi_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:34:03 by ngauthre          #+#    #+#             */
/*   Updated: 2025/08/13 10:42:59 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipes(int ***fds, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if ((*fds)[i][0])
			close((*fds)[i][0]);
		if ((*fds)[i][1])
			close((*fds)[i][1]);
		free((*fds)[i]);
		i++;
	}
	free(*fds);
}

void	close_all(int **fds, int start)
{
	int	max;

	max = *g_max_nb();
	while (start < max)
	{
		close_pipe(fds, start);
		start++;
	}
}

int	maxp(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

void	end_pipe(int code, t_commands *cmd, char **env, char *path)
{
	const char	*builtin[] = {"cd", "exit", "unset", "export", "echo", "env",
		"pwd"};
	int			i;
	t_commands	*cmd_tf;

	if (path)
	{
		free(path);
		free_p(cmd, env);
		exit(code);
	}
	i = 0;
	cmd_tf = get_index(cmd, cmd->stop_pars);
	while (cmd_tf && cmd_tf->arg && cmd_tf->arg[0] && i < 7)
	{
		if (strncmp(builtin[i], cmd_tf->arg[0], maxp(ft_strlen(builtin[i]),
					ft_strlen(cmd_tf->arg[0]))) == 0)
		{
			free_p(cmd, env);
			exit(code);
		}
		i++;
	}
}
