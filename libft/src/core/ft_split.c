/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:40:13 by nluchini          #+#    #+#             */
/*   Updated: 2025/10/16 14:10:28 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_count_word(const char *str, char del)
{
	int	strings;
	int	c;

	strings = 0;
	c = 0;
	if (*str == '\0')
		return (0);
	if (*str != del)
		strings++;
	while (str[c])
	{
		if (str[c] != del && c - 1 >= 0 && str[c - 1] == del)
			strings++;
		c++;
	}
	return (strings);
}

static int	ft_wlen(const char *str, char del)
{
	int	c;

	c = 0;
	while (*str && *str != del)
	{
		c++;
		str++;
	}
	return (c);
}

static char	*ft_strndup(const char *str, int n)
{
	char	*cpy;
	int		count;

	count = 0;
	cpy = ft_malloc(sizeof(char) * (n + 1));
	if (!cpy)
		return (NULL);
	while (count < n)
	{
		cpy[count] = str[count];
		count++;
	}
	cpy[count] = '\0';
	return (cpy);
}

static void	*__ft_free(char **res, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		ft_free(res[i]);
		i++;
	}
	ft_free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	int		wlen;

	if (!s)
		return (NULL);
	res = (char **)ft_malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (*s)
	{
		wlen = ft_wlen(s, c);
		if (*s == c)
		{
			s++;
			continue ;
		}
		res[i] = ft_strndup(s, wlen);
		if (!res[i])
			return (__ft_free(res, i));
		i++;
		s += wlen;
	}
	return (res[i] = NULL, res);
}
