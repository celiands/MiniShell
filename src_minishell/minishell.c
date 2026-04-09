/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:21:10 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/27 13:34:40 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*g_err_code(void)
{
	static int	v = 0;

	return (&v);
}

size_t	size_commands(t_commands *list)
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

static char	**cp_env(char **env)
{
	int		i;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while ((env)[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env)
		{
			new_env[i] = NULL;
			return (free_env(new_env), NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	main(int argc, char **argv, char **env)
{
	env = cp_env(env);
	if (!env)
		return (1);
	init_minishell(&env, argv, argc);
	loop_minishell(env);
	return (rl_clear_history(), free_env(env), 0);
}
