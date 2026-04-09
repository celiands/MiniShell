/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:53:43 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/24 17:47:17 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	ft_putline(char *s, int fd)
{
	write((unsigned)fd, s, ft_strlen2(s));
	write(fd, "\n", 1);
}

static int	sizeargv(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}

void	print_env(char **arg, char **env, int fd)
{
	int	i;

	i = 0;
	if (sizeargv(arg) != 1)
		return ;
	if (fd == -1)
		fd = 1;
	set_evar("_", "/usr/bin/env", env);
	while (env[i])
	{
		ft_putline(env[i], fd);
		i++;
	}
}
