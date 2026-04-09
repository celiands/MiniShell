/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:50:05 by cde-bard          #+#    #+#             */
/*   Updated: 2025/08/13 11:38:25 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//we are on a '$'
//we want to increment the read ptr input to after the the var name ($PATH)
//and increment the write ptr expanded_input to after the var content (\bin\...)
//sep is the separator we put instead of space
//return false if a malloc failed
bool	expand_dolar(char **input, char **expanded_input, char **env, char sep)
{
	char	*var;
	char	*var_content;

	var = var_name(*input);
	if (!var)
		return (false);
	if (ft_strlen(var) == 0)
	{
		expand_char(input, expanded_input, '$');
		return (free(var), true);
	}
	(*input) += ft_strlen(var) + 1;
	var_content = get_evar(var, env);
	while (var_content && *var_content)
	{
		if (*var_content == ' ')
			**expanded_input = sep;
		else
			**expanded_input = *var_content;
		(*expanded_input)++;
		var_content++;
	}
	free(var);
	return (true);
}

//we are on a '\"'
//we want to increment the read ptr input to after the quotes ("$PATH hello's")
//and increment the write ptr exp_input to after the content(\bin\.. hello's)
//we will interprete env var but the spaces will not become separators
//return false if a malloc failed
bool	expand_doublequote(char **input, char **expanded_input, char **env)
{
	(*input)++;
	while (**input != '\"')
	{
		if (**input == '$')
		{
			if (!expand_dolar(input, expanded_input, env, ' '))
				return (false);
		}
		else
		{
			**expanded_input = **input;
			(*expanded_input)++;
			(*input)++;
		}
	}
	(*input)++;
	return (true);
}

//just put the content of input in expand_input without interpretation
void	expand_singlequote(char **input, char **expanded_input)
{
	(*input)++;
	while (**input != '\'')
	{
		**expanded_input = **input;
		(*expanded_input)++;
		(*input)++;
	}
	(*input)++;
}

//we want to separate meta characters from the rest
//we put a separator before and after an instruction
//1 is here to specify it's a meta char
//list of instructions '<' '<<' '>' '>>' '|' 
//'<<' = 'k' and '>>' = 'l' (above on qwerty)
void	expand_meta(char **input, char **expanded_input)
{
	**expanded_input = '\n';
	(*expanded_input)++;
	**expanded_input = 1;
	(*expanded_input)++;
	if (**input == '<' && *((*input) + 1) == '<')
	{
		(*input)++;
		**expanded_input = 'k';
	}
	else if (**input == '>' && *((*input) + 1) == '>')
	{
		(*input)++;
		**expanded_input = 'l';
	}
	else
		**expanded_input = **input;
	(*expanded_input)++;
	(*input)++;
	**expanded_input = '\n';
	(*expanded_input)++;
}

//interprete $ " and ' and separate each word with \n
//reright input in expanded_input but interprete
//input and expanded input are used as pointers to where we read and write
//(that's why we increment them)
//return false if a malloc failed
bool	expand_in(char *input, char *expanded_input, char **env)
{
	while (*input)
	{
		if (*input == '$')
		{
			if (!expand_dolar(&input, &expanded_input, env, '\n'))
				return (false);
		}
		else if (*input == '\"')
		{
			if (!expand_doublequote(&input, &expanded_input, env))
				return (false);
		}
		else if (*input == '\'')
			expand_singlequote(&input, &expanded_input);
		else if (is_meta(*input))
			expand_meta(&input, &expanded_input);
		else if (is_whitespace(*input))
			expand_char(&input, &expanded_input, '\n');
		else
			expand_char(&input, &expanded_input, *input);
	}
	*expanded_input = 0;
	return (true);
}
