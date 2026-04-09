/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:33:58 by ngauthre          #+#    #+#             */
/*   Updated: 2025/08/13 11:15:21 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//interprete $ " and ' and separate each word with \n
//reright input in expanded_input but interprete
//input and expanded input are used as pointers to where we read and write
//(that's why we increment them)
//return false if a malloc failed
bool	expand_in_heredoc(char *input, char *expanded_input, char **env)
{
	while (*input)
	{
		if (*input == '$')
		{
			if (!expand_dolar(&input, &expanded_input, env, '\n'))
				return (false);
		}
		else
			expand_char(&input, &expanded_input, *input);
	}
	*expanded_input = 0;
	return (true);
}

char	*heredoc_expand(char *user_input, char **env)
{
	char	*expanded_user_input;

	expanded_user_input = malloc(sizemax_user_input(user_input, env) + 1);
	if (!expanded_user_input
		|| !expand_in_heredoc(user_input, expanded_user_input, env))
	{
		ft_putstr_fd("malloc failed\n", 2);
		if (expanded_user_input)
			free(expanded_user_input);
		free(user_input);
		set_err_code(254);
		return (0);
	}
	free(user_input);
	return (expanded_user_input);
}
