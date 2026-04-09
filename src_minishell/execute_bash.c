/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:55:40 by ngauthre          #+#    #+#             */
/*   Updated: 2025/08/14 11:09:33 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_commands *list, char ***env)
{
	if (strncmp(list->arg[0], "cd", 3) == 0)
		return (change_dir(list->arg + 1, env));
	if (strncmp(list->arg[0], "exit", 5) == 0)
		return (builtin_exit(list, *env));
	if (strncmp(list->arg[0], "echo", 5) == 0)
		return (echo(list->arg + 1, list->fd_outfile));
	if (strncmp(list->arg[0], "env", 4) == 0 && !list->arg[1])
		return (print_env(list->arg, *env, list->fd_outfile), 0);
	if (strncmp(list->arg[0], "unset", 6) == 0)
		return (unset(list->arg + 1, env));
	if (strncmp(list->arg[0], "export", 7) == 0)
		return (export(list->arg, env));
	if (strncmp(list->arg[0], "pwd", 4) == 0)
		return (pwd(list->arg, list->fd_outfile));
	return (127);
}
extern int	g_sigstatus;

static int	execute_basic(t_commands *list, char ***env)
{
	pid_t	pid;
	int		rt;

	set_evar("_", list->arg[0], *env);
	signal(SIGQUIT, &sigquit_handler);
	signal(SIGINT, &sig_handler);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		execute(list, *env);
	}
	pid_handler(&pid, 0);
	waitpid(pid, &rt, 0);
	if (g_sigstatus == 2)
		write(1, "\n", 1);
	return (rt);
}

int	execute_shell(t_commands *list, char ***env)
{
	const char	*builtin[] = {"cd", "exit", "unset",
		"export", "echo", "env", "pwd"};
	int			i;

	i = 0;
	if (!list || !list->arg)
		return (1);
	while (list && list->arg && list->arg[0] && i < 7)
	{
		if (strncmp(builtin[i], list->arg[0], max(ft_strlen(builtin[i]),
					ft_strlen(list->arg[0]))) == 0)
			return (execute_builtin(list, env));
		i++;
	}
	return (execute_basic(list, env));
}

int	processing(t_commands *list, char ***env)
{
	if (size_commands(list) > 1)
		return (pipex(list, *env));
	if (list->arg && *(list->arg))
		return (execute_shell(list, env));
	if (list->fd_infile != -1 || list->fd_outfile != -1)
		return (0);
	return (1);
}

void	execute(t_commands *cmd, char **env)
{
	char	*path;

	if (cmd->arg)
	{
		if (cmd->fd_infile == -1)
			cmd->fd_infile = 0;
		if (cmd->fd_outfile == -1)
			cmd->fd_outfile = 1;
		path = find_cmd(cmd->arg, env);
		dup2(cmd->fd_infile, STDIN_FILENO);
		dup2(cmd->fd_outfile, STDOUT_FILENO);
		if (cmd->fd_infile > 2)
			close(cmd->fd_infile);
		if (cmd->fd_outfile > 2)
			close(cmd->fd_outfile);
		if ((path))
		{
			execve(path, cmd->arg, env);
			free(path);
		}
	}
	free_command_list(cmd);
	free_env(env);
	ft_putendl_fd("Error : cmd not found", 2);
	exit(ERROR_CODE);
}
