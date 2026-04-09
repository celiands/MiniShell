/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:14:54 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/25 01:04:12 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	size_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	return (i);
}

static void	change_dir_core(char **current_path, char ***env)
{
	export_core("OLDPWD=", env);
	set_evar("OLDPWD", *current_path, *env);
	free(*current_path);
	*current_path = getcwd(NULL, 0);
	set_evar("PWD", *current_path, *env);
}

// cd
int	change_dir(char **path, char ***env)
{
	char	*current_path;

	if (size_path(path) == 0)
		return (0);
	if (size_path(path) != 1)
		return (ft_putendl_fd("error args", 2), 1);
	current_path = getcwd(NULL, 0);
	if (!current_path)
		return (ft_putendl_fd("memory err / getcwd", 2), 1);
	if (ft_strncmp("~", path[0], ft_strlen2(path[0])) == 0)
	{
		if (chdir(get_evar("HOME", *env)) == 0)
		{
			change_dir_core(&current_path, env);
		}
	}
	else if (chdir(path[0]) == 0)
	{
		change_dir_core(&current_path, env);
	}
	else
		return (free(current_path), ft_putendl_fd("error", 2), 1);
	return (free(current_path), 0);
}
