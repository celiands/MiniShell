/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:01:36 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/28 20:27:52 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigstatus = 0;

void	sigint_handler(int code)
{
	(void)code;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	set_err_code(130);
	g_sigstatus = 2;
}

void	sigint_heredoc(int code)
{
	(void)code;
	close (0);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_done = 1;
	g_sigstatus = 2;
}

void	sig_handler(int code)
{
	g_sigstatus = code;
}

pid_t	*pid_handler(pid_t *value, int mod)
{
	static pid_t	pid[1024];
	static int		i = 0;
	static int		j = 0;

	if (value != NULL)
	{
		pid[i++] = *value;
	}
	if (mod == 1)
		return (&pid[j++]);
	else if (mod == 2)
	{
		ft_memset(pid, 0, sizeof(pid));
		j = 0;
		i = 0;
		return (NULL);
	}
	else if (mod == 3)
		return (j = 0, NULL);
	else
		return (NULL);
}

void	sigquit_handler(int code)
{
	pid_t	*pid;

	pid = pid_handler(NULL, 3);
	pid = pid_handler(NULL, 1);
	if (pid && *pid > 0)
	{
		write(2, "Quit (Core Dumped)\n", 19);
		while (*pid != 0)
		{
			kill(*pid, code);
			pid = pid_handler(NULL, 1);
		}
		pid = pid_handler(NULL, 2);
	}
	g_sigstatus = code;
	set_err_code(131);
}
