/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:50:17 by cde-bard          #+#    #+#             */
/*   Updated: 2025/06/28 20:30:45 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_sizemax_user_input(int *i, int *size)
{
	*i = 0;
	*size = 0;
}

//free the tab but doesn't put it's pointer to 0
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

//free the list (and closes the fds) but doesn't put it's pointer to 0
void	free_command_list(t_commands *list)
{
	t_commands	*next;

	while (list)
	{
		next = list -> next;
		if (list -> arg)
			free_tab(list -> arg);
		if (list -> fd_infile != -1)
			close(list -> fd_infile);
		if (list -> fd_outfile != -1)
			close(list -> fd_outfile);
		free(list);
		list = next;
	}
}

void	heredoc_norm_close(int *fd_dup)
{
	dup2(*fd_dup, STDIN_FILENO);
	close(*fd_dup);
}

//just write the char
void	expand_char(char **input, char **expanded_input, char c)
{
	**expanded_input = c;
	(*expanded_input)++;
	(*input)++;
}
