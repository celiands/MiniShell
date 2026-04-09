/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:13:06 by cde-bard          #+#    #+#             */
/*   Updated: 2025/08/13 11:17:29 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

//if we couldn't open, freed and close but return true to keep parsing the
//other commandes (after the pipe)
bool	redir_in(char *word, t_commands *command)
{
	if (command -> fd_infile > 0)
		close(command -> fd_infile);
	command -> fd_infile = open(word, O_RDONLY);
	if (command -> fd_infile < 0)
	{
		ft_putstr_fd("could't open ", 2);
		ft_putendl_fd(word, 2);
		command -> stop_pars = true;
		free_tab(command -> arg);
		command -> arg = 0;
		if (command -> fd_outfile > 0)
			close(command -> fd_outfile);
		command -> fd_outfile = -1;
	}
	return (true);
}
extern int	g_sigstatus;

//return false if readline failed to malloc
bool	heredoc(char *word, t_commands *command, char **env)
{
	int		pipe_fd[2];
	char	*line;
	int		fd_dup;

	if (pipe(pipe_fd) == -1)
		return (ft_putstr_fd("pipe failed\n", 2), set_err_code(254), false);
	signal(SIGINT, &sigint_heredoc);
	fd_dup = dup(STDIN_FILENO);
	line = readline(">");
	while (g_sigstatus != 2 && line && ft_strncmp(line, word, UINT_MAX))
	{
		ft_putendl_fd(line = heredoc_expand(line, env), pipe_fd[1]);
		free(line);
		line = readline(">");
	}
	close(pipe_fd[1]);
	heredoc_norm_close(&fd_dup);
	if (command -> fd_infile > 0)
		close(command -> fd_infile);
	command -> fd_infile = pipe_fd[0];
	if (line)
		free(line);
	else
		return (false);
	return (true);
}

//if an open failed, we stop parsing until the next pipe (stop_pars = true)
//return true (return false is for no parsing at all and freeing everything)
bool	redir_out(char *word, t_commands *command, int open_type)
{
	if (command -> fd_outfile > 0)
		close(command -> fd_outfile);
	command -> fd_outfile = open(word, O_WRONLY | O_CREAT | open_type, 0666);
	if (command -> fd_outfile < 0)
	{
		ft_putstr_fd("could't open ", 2);
		ft_putendl_fd(word, 2);
		command -> stop_pars = true;
		free_tab(command -> arg);
		command -> arg = 0;
		if (command -> fd_infile > 0)
			close(command -> fd_infile);
		command -> fd_infile = -1;
	}
	return (true);
}

//add a dup of the arg in *arg[], return false to free evrything if malloc fail
bool	add_arg(char *word, t_commands *command)
{
	int	i;

	i = 0;
	while ((command -> arg)[i])
		i++;
	(command -> arg)[i] = ft_strdup(word);
	if ((command -> arg)[i] == 0)
	{
		ft_putstr_fd("malloc failed\n", 2);
		return (set_err_code(254), false);
	}
	return (true);
}

//parse one word of the split and return the increment of i
//we know that split[0] is not '\0' or '|'
//return false if syntax error
//return false if a malloc failed so we just doesn't parse and return null
//return true but with an empty command if open failed
//if an open failed, return true but the command is marqued as stop_parsing
bool	parse_command(char **split, t_commands *command, int *i, char **env)
{
	bool	ret;

	if (split[0][0] == 1)
	{
		if (split[0][1] == '<')
			ret = redir_in(split[1], command);
		else if (split[0][1] == 'k')
			ret = heredoc(split[1], command, env);
		else if (split[0][1] == '>')
			ret = redir_out(split[1], command, O_TRUNC);
		else if (split[0][1] == 'l')
			ret = redir_out(split[1], command, O_APPEND);
	}
	else
	{
		ret = add_arg(split[0], command);
		(*i)--;
	}
	(*i) += 2;
	return (ret);
}
