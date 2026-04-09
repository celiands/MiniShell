/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:28:59 by cde-bard          #+#    #+#             */
/*   Updated: 2025/08/13 10:34:14 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_redir(char *n)
{
	if (*n == 1 && (n[1] == '<' || n[1] == '>' || n[1] == 'k' || n[1] == 'l'))
		return (true);
	else
		return (false);
}

bool	is_pipe(char *node)
{
	if (node[0] == 1 && node[1] == '|')
		return (true);
	else
		return (false);
}

bool	is_whitespace(char c)
{
	if (c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
	{
		return (true);
	}
	return (false);
}

//return true if syntax error
bool	syntax_error(char **split)
{
	int	i;

	i = 0;
	if (split && split[0])
	{
		while (split[i + 1])
		{
			if (is_pipe(split[i])
				&& (is_pipe(split[i + 1]) || split[i + 1][0] == 0))
				return (true);
			if (split[i][0] == 1 && !is_pipe(split[i])
				&& (split[i + 1][0] == 1 || split[i + 1][0] == 0))
				return (true);
			i++;
		}
		if (is_pipe(split[0]) || split[i][0] == 1)
			return (true);
	}
	return (false);
}
