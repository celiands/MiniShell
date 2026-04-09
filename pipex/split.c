/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:42:15 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/21 16:04:37 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static int	get_words(char const *s, char c)
// {
// 	const char	*ns = s;
// 	int			words;

// 	words = 0;
// 	while (*ns)
// 	{
// 		if (*ns != c && (*(ns + 1) == c || *(ns + 1) == 0))
// 			words += 1;
// 		ns++;
// 	}
// 	return (words);
// }

// static int	add_to(char **dst, const char **src, char c)
// {
// 	size_t	j;
// 	size_t	i;

// 	j = 0;
// 	i = 0;
// 	while (src[0][0] == c)
// 		src[0]++;
// 	while (src[0][j] != c && src[0][j])
// 		j++;
// 	if (j != 0)
// 	{
// 		dst[0] = malloc(sizeof(char) * (j + 1));
// 		if (!dst[0])
// 			return (0);
// 		dst[0][j] = '\0';
// 		i = j;
// 		while (j-- > 0)
// 		{
// 			dst[0][j] = src[0][j];
// 		}
// 	}
// 	return (i);
// }

void	unlimited_free_works(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

// char	**ft_split(char const *s, char c)
// {
// 	int		i;
// 	int		j;
// 	char	**split;
// 	int		max;

// 	if (s == NULL)
// 		return (NULL);
// 	max = get_words(s, c);
// 	split = malloc(sizeof(char *) * (max + 1));
// 	if (!split)
// 		return (NULL);
// 	split[max] = NULL;
// 	i = 0;
// 	while (i < max)
// 	{
// 		j = add_to(&split[i], &s, c);
// 		if (!split[i++] || j == 0)
// 			return (unlimited_free_works(split), NULL);
// 		s += j + 1;
// 	}
// 	return (split);
// }
