/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:38:58 by ngauthre          #+#    #+#             */
/*   Updated: 2025/08/08 13:08:36 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*f_join(char const *s1, char sep, char const *s2)
{
	char	*j;

	j = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!j)
		return (NULL);
	ft_strlcpy(j, s1, ft_strlen(s1) + 1);
	j[ft_strlen(s1)] = sep;
	ft_strlcpy(j + ft_strlen(s1)+1, s2, ft_strlen(s2) + 1);
	j[ft_strlen(s1) + ft_strlen(s2) + 1] = '\0';
	return (j);
}

void	pipex_core(t_commands *list, char **env, int **fds, int nb)
{
	int	i;

	i = 0;
	signal(SIGQUIT, &sigquit_handler);
	signal(SIGINT, &sig_handler);
	while (i < nb)
	{
		child_init(list, env, fds, i);
		i++;
	}
}

void	close_pipe(int	**fd, int id)
{
	close(fd[id][1]);
	close(fd[id][0]);
}

void	sig_init_p(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	print_error(char *s, int i)
{
	ft_putstr_fd(s, 2);
	strerror(i);
	exit(i);
}
