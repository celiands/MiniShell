/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:47:07 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/25 02:38:17 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	echo(char **prompt, int fd)
{
	int	i;
	int	end;

	i = 0;
	end = 0;
	if (fd == -1)
		fd = 1;
	if (!(prompt) || !(*prompt) || !(**prompt))
		return (ft_putstr_fd("\n", fd), 0);
	if (ft_strncmp(prompt[0], "-n", 3) == 0)
		end = 1;
	while (prompt && prompt[i + end])
	{
		if (i > 0)
			ft_putstr_fd(" ", fd);
		ft_putstr_fd(prompt[i + end], fd);
		i++;
	}
	if (end == 0)
		ft_putstr_fd("\n", fd);
	if (write(fd, "", 0) == -1)
		return (printf("Write error\n"), 1);
	return (0);
}
