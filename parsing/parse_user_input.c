/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:28:59 by cde-bard          #+#    #+#             */
/*   Updated: 2025/08/13 11:47:36 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//return true if the quotes of the input are correct
bool	check_unclosed_quotes(char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if (user_input[i] == '\"')
		{
			i++;
			while (user_input[i] && user_input[i] != '\"')
				i++;
			if (!user_input[i])
				return (false);
		}
		else if (user_input[i] == '\'')
		{
			i++;
			while (user_input[i] && user_input[i] != '\'')
				i++;
			if (!user_input[i])
				return (false);
		}
		i++;
	}
	return (true);
}

//'$' is meta ' ' and '\0' are not
bool	is_meta(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '\"' || c == '\'' || c == '$')
		return (true);
	return (false);
}

//separate the name of the var in an allocated string
//ex : "$PATH<infile" or "$PATH arg" return "PATH"
//return 0 if malloc failed
char	*var_name(char *start)
{
	int	i;

	i = 1;
	while (start[i] && !is_meta(start[i]) && start[i] != ' ')
	{
		i++;
	}
	return (ft_substr(start, 1, i - 1));
}

//return the size of the input with the variables expanded
//return -2 if malloc failed
int	sizemax_user_input(char *user_input, char **env)
{
	int		i;
	int		size;
	char	*var;

	init_sizemax_user_input(&i, &size);
	while (user_input[i] && size >= 0)
	{
		if (user_input[i] == '$')
		{
			var = var_name(&user_input[i]);
			if (!var)
				return (-2);
			i ++;
			size += ft_strlen(get_evar(var, env)) + 1;
			free(var);
		}
		else
		{
			if (is_meta(user_input[i]))
				size += 3;
			size++;
			i++;
		}
	}
	return (size);
}

//return 0 if error
//return a list of t_commands and free the user input (do not input null)
//ps readline return une chaine vide mais jamais null sauf si erreur de malloc
t_commands	*parse_user_input(char *user_input, char **env)
{
	char	*expanded_user_input;
	char	**split;

	if (!check_unclosed_quotes(user_input))
	{
		printf("unclosed quotes\n");
		free(user_input);
		return (set_err_code(2), (t_commands *)0);
	}
	expanded_user_input = malloc(sizemax_user_input(user_input, env) + 1);
	if (!expanded_user_input
		|| !expand_in(user_input, expanded_user_input, env))
	{
		printf("malloc failed\n");
		if (expanded_user_input)
			free(expanded_user_input);
		free(user_input);
		return (set_err_code(254), (t_commands *)0);
	}
	split = ft_split(expanded_user_input, '\n');
	free(user_input);
	free(expanded_user_input);
	if (!split)
		return (printf("malloc failed\n"), set_err_code(254), (t_commands *)0);
	return (parse_in_list(split, env));
}
