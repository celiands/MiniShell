/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:18:53 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/28 21:07:53 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

//environment variable size
size_t	evs(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if ((str[i] != '='))
		return (-1);
	return (i);
}

size_t	env_size(char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

//(find str in str (seek little in big))
int	fsis(const char *big, const char *little, size_t len)
{
	const char	*l = little;
	const char	*b = big;
	size_t		i;

	if (!*l)
		return (1);
	if (ft_strlen2(big) < len)
		len = ft_strlen2(big);
	while (*b && len-- > 0)
	{
		i = 0;
		while (b[i] == l[i] && len + 1 > i)
			i++;
		if (!l[i])
			return (0);
		b++;
	}
	return (1);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
		free(env[i++]);
	free(env);
}
