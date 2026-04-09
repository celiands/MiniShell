/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_in_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:42:59 by cde-bard          #+#    #+#             */
/*   Updated: 2025/08/13 11:10:14 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//return the last command of the list
t_commands	*last_command(t_commands *list)
{
	if (!list)
		return (0);
	while (list -> next)
		list = list -> next;
	return (list);
}

//return a command with nothing
t_commands	*initialize_command(int count_arg)
{
	t_commands	*command;

	command = malloc(sizeof(t_commands));
	if (!command)
		return (0);
	command -> arg = 0;
	if (count_arg)
	{
		command -> arg = calloc(sizeof(char *), count_arg + 1);
		if (!(command -> arg))
			return (free(command), (t_commands *)0);
	}
	command -> fd_infile = -1;
	command -> fd_outfile = -1;
	command -> stop_pars = 0;
	command -> next = 0;
	return (command);
}

//count the number of arguments until the next pipe
int	count_arg(char **split)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (split[++i] != 0 && !is_pipe(split[i]))
	{
		if (is_redir(split[i]))
			i++;
		else
			count++;
	}
	return (count);
}

//append the command at the end of the list
//the pointer split is on a pipe "|" "<" "outfile.txt" "arg1" "arg2" "|" ...
//when return false, evrything is freed in parse_in_list()
bool	append_command(char **split, t_commands	**list, char **env)
{
	int			i;
	t_commands	*command;

	i = 1;
	if (!(*list))
	{
		(*list) = initialize_command(count_arg(split));
		command = (*list);
	}
	else
	{
		command = last_command(*list);
		command -> next = initialize_command(count_arg(split));
		command = command -> next;
	}
	if (!command)
		return (ft_putstr_fd("malloc error\n", 2), false);
	while (split[i] != 0 && !is_pipe(split[i]) && !(command -> stop_pars))
	{
		if (!parse_command(&split[i], command, &i, env))
			return (false);
	}
	return (true);
}

t_commands	*parse_in_list(char **split, char **env)
{
	t_commands	*list;
	int			i;
	bool		succeed_to_append;

	i = 0;
	list = 0;
	if (syntax_error(split))
	{
		ft_putstr_fd("Syntax error\n", 2);
		return (set_err_code(2), free_tab(split), list);
	}
	succeed_to_append = append_command(&split[i - 1], &list, env);
	while (split[i] && succeed_to_append)
	{
		if (is_pipe(split[i]))
			succeed_to_append = append_command(&split[i], &list, env);
		i++;
	}
	free_tab(split);
	if (!succeed_to_append)
	{
		free_command_list(list);
		return (set_err_code(254), (t_commands *)0);
	}
	return (list);
}
