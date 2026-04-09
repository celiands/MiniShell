/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:05:50 by ngauthre          #+#    #+#             */
/*   Updated: 2025/08/08 12:20:15 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//faire ft pour shell lvl

void	siginit_minishell(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

extern int	g_sigstatus;

void	set_err_code(int i)
{
	char	*v;

	if (g_sigstatus != 0)
		i = g_sigstatus + 128;
	v = ft_itoa(i % 255);
	if (!v)
		return ;
	ft_strlcpy(err_code(), v, 13);
	free(v);
}

static void	set_shlvl(char **env)
{
	char	*c_evar;
	char	*val;

	c_evar = get_evar("SHLVL", env);
	if (*c_evar == '\0')
		set_evar("SHLVL", "1", env);
	else
	{
		val = ft_itoa(ft_atoi(c_evar) + 1);
		if (val)
		{
			set_evar("SHLVL", val, env);
			free(val);
		}
		else
			set_evar("SHLVL", "1", env);
	}
}

int	init_minishell(char ***env, char **argv, int argc)
{
	const char	*v[] = {"PWD", "SHLVL", "_", NULL};
	const char	*e[] = {"PWD=", "SHLVL=", "_=", NULL};
	int			i;	
	char		*val;

	(void)argv;
	(void)argc;
	i = 0;
	while (e[i])
	{
		if (get_evar((char *)v[i], *env) == NULL)
			export_core((char *)e[i], env);
		i++;
	}
	set_shlvl(*env);
	val = getcwd(NULL, 0);
	if (!val)
		return (1);
	set_evar("PWD", val, *env);
	set_evar("_", argv[0], *env);
	set_err_code(0);
	free(val);
	return (0);
}
