/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_multi_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:26:55 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/27 12:40:24 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	choose_in(t_commands *cmd, int **fds, int current)
{
	if (cmd->fd_outfile == -1)
		cmd->fd_outfile = fds[current][1];
	if (cmd->fd_infile == -1)
		cmd->fd_infile = 0;
}

int	*g_max_nb(void)
{
	static int	maxnb = -1;

	return (&maxnb);
}

int	****g_addr_pipes(void)
{
	static int	***addr;

	return (&addr);
}

void	choose_out(t_commands *cmd, int **fds, int current)
{
	if (cmd->fd_outfile == -1)
	{
		if (*g_max_nb() == current + 1)
			cmd->fd_outfile = 1;
		else
			cmd->fd_outfile = fds[current + 1][1];
	}
	if (cmd->fd_infile == -1)
		cmd->fd_infile = fds[current][0];
}

int	**create_pipes(int nb)
{
	int	**fds;
	int	i;

	fds = malloc(sizeof(int *) * nb);
	if (!fds)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (!fds[i++] || pipe(fds[i - 1]) == -1)
		{
			free_pipes(&fds, i);
			print_error("pipe error\n", 2);
		}
	}
	return (fds);
}
