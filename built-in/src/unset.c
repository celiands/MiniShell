/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:20:42 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/24 17:35:03 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	remove_env(int index, char ***env)
{
	int		i;
	int		rt;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (env_size(*env)));
	if (!new_env)
		return (1);
	i = 0;
	rt = 0;
	while ((*env)[i])
	{
		if (i != index)
			new_env[i - rt] = (*env)[i];
		else
		{
			rt = 1;
			free((*env)[i]);
			(*env)[i] = NULL;
		}
		i++;
	}
	new_env[i - rt] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

int	unset_core(char *var, char ***env)
{
	int	i;

	i = 0;
	if (ft_isdigit2(*var) != 0 || (*var != '_' && !ft_isalnum2(*var)))
		return (1);
	while ((*env)[i])
	{
		if (ft_strncmp(var, (*env)[i], evs((*env)[i])) == 0)
			return (remove_env(i, env));
		i++;
	}
	return (0);
}

int	unset(char **args, char ***env)
{
	int	i;
	int	rt;
	int	old_rt;

	i = 0;
	old_rt = 0;
	if (!args || !args[0])
		return (1);
	while (args && args[i])
	{
		rt = unset_core(args[i], env);
		if (old_rt < rt)
			old_rt = rt;
		i++;
	}
	return (old_rt);
}
