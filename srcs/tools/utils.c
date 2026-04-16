/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:39:10 by sruff             #+#    #+#             */
/*   Updated: 2026/04/16 13:39:26 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*malloc_strdup(const char *src)
{
	char	*dest;
	size_t	len;

	if (!src)
		return (NULL);
	len = ft_strlen(src) + 1;
	dest = ft_malloc(len);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, src, len);
	return (dest);
}

char	**str_array_dup(char **src, int32_t height)
{
	char	**dest;
	int32_t	i;

	if (!src)
		return (NULL);
	dest = ft_malloc(sizeof(char *) * (height + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < height)
	{
		dest[i] = malloc_strdup(src[i]);
		if (!dest[i])
		{
			return (NULL);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

int32_t	validate_texture_file(const char *path)
{
	int32_t	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

char	*ft_strpbrk(const char *s, const char *charset)
{
	while (*s)
	{
		if (ft_strchr(charset, *s))
			return ((char *)s);
		s++;
	}
	return (NULL);
}
