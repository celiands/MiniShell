/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_evar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:40:30 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/24 17:37:48 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*find_evar(const char *big, const char *little, size_t len)
{
	const char	*l = little;
	const char	*b = big;
	size_t		i;

	if (!*l)
		return ((char *)b);
	if (ft_strlen2(big) < len)
		len = ft_strlen2(big);
	while (*b && len-- > 0)
	{
		i = 0;
		while (b[i] == l[i] && len + 1 > i)
			i++;
		if (!l[i])
			return ((char *)b + i + 1);
		b++;
	}
	return (NULL);
}

char	*get_evar(char *var, char **env)
{
	int	i;

	i = 0;
	if (ft_strncmp(var, "?", 1) == 0)
		return (err_code());
	while (env && (env)[i])
	{
		if ((ft_strlen2(var) == evs((env)[i]))
			&& fsis((env)[i], var, ft_strlen2(var)) == 0)
			return (find_evar(env[i], var, ft_strlen2(var)));
		i++;
	}
	return (NULL);
}
