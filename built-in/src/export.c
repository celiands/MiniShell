/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:44:10 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/28 21:07:10 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	in_env(char *str, char **env)
{
	int	i;

	i = 0;
	while (env && (env)[i])
	{
		if (ft_strncmp(str, env[i], evs(env[i])) == 0)
		{
			free(env[i]);
			env[i] = ft_strdup2(str);
			return (0);
		}
		i++;
	}
	return (1);
}

//copy env for add
static char	**cp_env_fadd(char **env)
{
	int		i;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (env_size(env) + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env && (env)[i])
	{
		new_env[i] = ft_strdup2(env[i]);
		if (!new_env[i])
			return (new_env[i] = NULL, free_env(new_env), NULL);
		i++;
	}
	new_env[i] = NULL;
	new_env[i + 1] = NULL;
	return (new_env);
}

int	export_core(char *var, char ***env)
{
	char	**new_env;

	if (*var == '=' || ft_isdigit2(*var) != 0
		|| ft_strchr2(var + 1, '=') == NULL)
		return (ft_putendl_fd("not valid id", 2), 1);
	if (in_env(var, *env) == 0)
		return (0);
	new_env = cp_env_fadd(*env);
	if (!new_env)
		return (1);
	new_env[env_size(new_env)] = ft_strdup2(var);
	free_env(*env);
	*env = new_env;
	return (0);
}

int	export(char **args, char ***env)
{
	int	i;
	int	rt;
	int	old_rt;

	i = 1;
	old_rt = 0;
	while (args && args[i])
	{
		rt = export_core(args[i], env);
		if (old_rt < rt)
			old_rt = rt;
		i++;
	}
	return (old_rt);
}
