/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:23:49 by ngauthre          #+#    #+#             */
/*   Updated: 2025/08/13 12:30:01 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1_process(t_commands *cmd, char **env, int **fd, int i)
{
	char	*path;

	choose_in(cmd, fd, i);
	if (cmd->fd_infile < 0)
	{
		free_p(cmd, env);
		print_error("No such file or directory\n", 127);
	}
	if (!(cmd->arg))
	{
		free_p(cmd, env);
		exit(1);
	}
	path = find_cmd(cmd->arg, env);
	redir_child1(cmd, fd, i);
	close_all(fd, i + 1);
	cmd->stop_pars = i;
	end_pipe(execute_(cmd, path, &env), cmd, env, path);
	free_p(cmd, env);
	print_error("Error : command not found\n", 127);
}

void	child2_process(t_commands *cmd_o, char **env, int **fds, int i)
{
	char		*path;
	t_commands	*cmd;

	cmd = get_index(cmd_o, i + 1);
	choose_out(cmd, fds, i);
	if (cmd->fd_outfile < 0)
	{
		free_p(cmd_o, env);
		print_error("No such file or directory\n", 127);
	}
	if (!(cmd->arg))
	{
		free_p(cmd_o, env);
		exit(1);
	}
	path = find_cmd(cmd->arg, env);
	redir_child2(cmd, fds, i);
	close_all(fds, i + 1);
	cmd_o->stop_pars = i + 1;
	end_pipe(execute_(cmd, path, &env), cmd_o, env, path);
	free_p(cmd_o, env);
	print_error("Error : command not found\n", 127);
}

int	child_init(t_commands *cmd, char **env, int **fd, int id)
{
	pid_t	child_1;
	pid_t	child_2;

	if (id == 0)
	{
		child_1 = fork();
		if (child_1 == 0)
		{
			sig_init_p();
			pid_handler(&child_1, 0);
			child1_process(cmd, env, fd, id);
		}
	}
	child_2 = fork();
	if (child_2 == 0)
	{
		sig_init_p();
		pid_handler(&child_2, 0);
		child2_process(cmd, env, fd, id);
	}
	close_pipe(fd, id);
	if (id == 0)
		pid_handler(&child_1, 0);
	pid_handler(&child_2, 0);
	return (0);
}

t_commands	*get_index(t_commands *list, int i)
{
	int			j;
	t_commands	*rt;

	j = 0;
	rt = list;
	while (j != i && rt)
	{
		rt = rt->next;
		j++;
	}
	return (rt);
}

int	pipex(t_commands *list, char **env)
{
	int	**fds;
	int	rt;
	int	nb;
	int	i;

	*g_max_nb() = size_commands_p(list) - 1;
	nb = *g_max_nb();
	fds = create_pipes(nb);
	if (fds == NULL)
		print_error("error alloc\n", 2);
	*g_addr_pipes() = &fds;
	pipex_core(list, env, fds, nb);
	pid_handler(NULL, 3);
	i = 0;
	while (i - 1 < nb)
	{
		waitpid(*pid_handler(NULL, 1), &rt, 0);
		i++;
	}
	free_pipes(&fds, nb);
	if (g_sigstatus == 2)
		write(1, "\n", 1);
	return (rt >> 8);
}
