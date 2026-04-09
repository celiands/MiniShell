/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:34:42 by ngauthre          #+#    #+#             */
/*   Updated: 2025/08/13 12:29:25 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_paths(char **envp)
{
	int	i;

	i = 0;
	if (envp[0] == NULL)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*find_cmd(char **cmd, char **env)
{
	char		**all_paths;
	int			i;
	char		*joined;
	struct stat	sb;

	if (access(cmd[0], F_OK | X_OK) == 0 && stat(cmd[0], &sb) != -1
		&& !S_ISDIR(sb.st_mode))
		return (ft_strdup(cmd[0]));
	if (cmd[0][0] == '/')
		return (NULL);
	joined = NULL;
	all_paths = find_paths(env);
	i = 0;
	while (all_paths != NULL && all_paths[++i - 1])
	{
		joined = f_join(all_paths[i - 1], '/', cmd[0]);
		if (!joined)
			return (NULL);
		if (access(joined, F_OK | X_OK) == 0)
			break ;
		free(joined);
		joined = NULL;
	}
	return (unlimited_free_works(all_paths), joined);
}

void	free_p(t_commands *cmd, char **env)
{
	free_command_list(cmd);
	free_pipes(*g_addr_pipes(), *g_max_nb());
	free_env(env);
}

void	redir_child1(t_commands *cmd, int **fd, int i)
{
	dup2(cmd->fd_outfile, STDOUT_FILENO);
	if (cmd->fd_outfile != 1)
		close(cmd->fd_outfile);
	close(fd[i][0]);
	dup2(cmd->fd_infile, STDIN_FILENO);
	if (cmd->fd_infile != 0)
		close(cmd->fd_infile);
}

void	redir_child2(t_commands *cmd, int **fds, int i)
{
	dup2(cmd->fd_infile, STDIN_FILENO);
	close(cmd->fd_infile);
	close(fds[i][1]);
	dup2(cmd->fd_outfile, STDOUT_FILENO);
	if (cmd->fd_outfile != 1)
		close(cmd->fd_outfile);
}
