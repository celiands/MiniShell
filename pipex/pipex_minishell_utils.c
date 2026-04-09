/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_minishell_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:21:21 by ngauthre          #+#    #+#             */
/*   Updated: 2025/08/08 13:47:58 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	size_commands_p(t_commands *list)
{
	t_commands	*start;
	size_t		i;

	i = 0;
	start = list;
	while (start)
	{
		start = start->next;
		i++;
	}
	return (i);
}

int	execute_builtin_p(t_commands *list, char ***env)
{
	if (strncmp(list->arg[0], "cd", 3) == 0)
		return (change_dir(list->arg + 1, env));
	if (strncmp(list->arg[0], "exit", 5) == 0)
		return (builtin_exit(list, *env));
	if (strncmp(list->arg[0], "echo", 5) == 0)
		return (echo(list->arg + 1, 1));
	if (strncmp(list->arg[0], "env", 4) == 0)
		return (print_env(list->arg, *env, 1), 0);
	if (strncmp(list->arg[0], "unset", 6) == 0)
		return (unset(list->arg + 1, env));
	if (strncmp(list->arg[0], "export", 7) == 0)
		return (export(list->arg, env));
	if (strncmp(list->arg[0], "pwd", 4) == 0)
		return (pwd(list->arg, 1));
	return (0);
}

// il faut qnd mm faire cd car si deplacement impossible, no such file or dir
int	execute_(t_commands *cmd, char *path, char ***env)
{
	const char	*builtin[] = {"cd", "exit", "unset", "export", "echo", "env",
		"pwd"};
	int			i;
	struct stat	sb;

	i = 0;
	if (!cmd || !cmd->arg || *(cmd->arg) == 0 || **(cmd->arg) == 0)
		return (1);
	while (cmd && cmd->arg && cmd->arg[0] && i < 7)
	{
		if (strncmp(builtin[i], cmd->arg[0], maxp(ft_strlen(builtin[i]),
					ft_strlen(cmd->arg[0]))) == 0)
		{
			return (execute_builtin_p(cmd, env));
		}
		i++;
	}
	if (path != NULL && stat(path, &sb) != -1 && !S_ISDIR(sb.st_mode))
		execve(path, cmd->arg, *env);
	return (1);
}
