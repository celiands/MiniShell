/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:09:37 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/28 21:04:08 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	pwd(char **args, int fd)
{
	char	*get_cwd_var;

	(void)args;
	if (fd == -1)
		fd = 1;
	get_cwd_var = getcwd(NULL, 0);
	if (!get_cwd_var)
		return (1);
	ft_putendl_fd(get_cwd_var, fd);
	return (free(get_cwd_var), 0);
}
