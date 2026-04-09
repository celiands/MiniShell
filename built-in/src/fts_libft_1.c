/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_libft_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngauthre <ngauthre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:09:07 by ngauthre          #+#    #+#             */
/*   Updated: 2025/06/24 17:38:22 by ngauthre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// /!\ libft
size_t	ft_strlen2(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

// /!\ libft
char	*ft_strdup2(char *s)
{
	char	*newstr;
	int		i;

	newstr = malloc(sizeof(char) * (ft_strlen2(s) + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

// /!\ libft
char	*ft_strchr2(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

// /!\ libft
size_t	ft_strlcpy2(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (++i < n && src[i - 1])
		dst[i - 1] = src[i - 1];
	if (n > 0)
		dst[i - 1] = '\0';
	return (ft_strlen2(src));
}

// /!\ libft
char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*j;

	j = malloc(sizeof(char) * (ft_strlen2(s1) + ft_strlen2(s2) + 1));
	if (!j)
		return (NULL);
	ft_strlcpy2(j, s1, ft_strlen2(s1) + 1);
	ft_strlcpy2(j + ft_strlen2(s1), s2, ft_strlen2(s2) + 1);
	j[ft_strlen2(s1) + ft_strlen2(s2)] = '\0';
	return (j);
}
