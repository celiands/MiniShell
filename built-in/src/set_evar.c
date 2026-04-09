/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_evar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:09:38 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/24 17:36:34 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*ndup(char *s, int n)
{
	char	*newstr;
	int		i;

	newstr = malloc(sizeof(char) * (n + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

static int	change_var(int index, char *value, char **env)
{
	char	*name;

	name = ndup(env[index], evs(env[index]) + 1);
	free(env[index]);
	env[index] = ft_strjoin2(name, value);
	free(name);
	if (!env[index])
		return (1);
	return (0);
}

int	set_evar(char *var, char *value, char **env)
{
	int	i;

	i = 0;
	while ((env)[i])
	{
		if ((ft_strlen2(var) == evs((env)[i]))
			&& fsis((env)[i], var, ft_strlen2(var)) == 0)
			return (change_var(i, value, env));
		i++;
	}
	return (1);
}
