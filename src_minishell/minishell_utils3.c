/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:38:39 by ngauthre          #+#    #+#             */
/*   Updated: 2025/08/13 12:31:02 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_command_list(t_commands *start)
// {
// 	t_commands *list;

// 	list = start;
// 	while (list)
// 	{
// 		if (list -> arg)
// 		{
// 			printf("cmd : %s\n", list -> arg[0]);
// 			printf("arg :");
// 			for (int i = 0; (list -> arg)[i]; i++)
// 				printf(" %s", (list -> arg)[i]);
// 		}
// 		else
// 			printf("no arg");
// 		printf("\nfd_infile : %d\n", list -> fd_infile);
// 		printf("fd_outfile : %d\n", list -> fd_outfile);
// 		list = list -> next;
// 	}
// }

bool	quote_only(const char *str)
{
	int	i;

	i = 0;
	if (!check_unclosed_quotes((char *)str))
	{
		return (false);
	}
	while (str && str[i])
	{
		if (!is_whitespace(str[i]) && str[i] != '\'' && str[i] != '\"')
			return (false);
		i++;
	}
	return (ft_putendl_fd("Error : cmd not found", 2), set_err_code(127), true);
}

bool	check_no_cmd(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!is_whitespace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	loop_minishell(char **env)
{
	char		*prompt;
	t_commands	*list;

	while (1)
	{
		siginit_minishell();
		prompt = readline("MiniShell >");
		g_sigstatus = 0;
		if (!prompt)
			builtin_exit(NULL, env);
		add_history(prompt);
		if (!check_no_cmd(prompt) && !quote_only(prompt))
		{
			list = parse_user_input(prompt, env);
			if ((list) != 0)
			{
				set_err_code(processing(list, &env));
				free_command_list(list);
				pid_handler(NULL, 2);
			}
		}
		else
			free(prompt);
	}
}
