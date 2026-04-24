/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:22:46 by sruff             #+#    #+#             */
/*   Updated: 2026/04/24 16:57:45 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		dest[i] = ft_strdup(src[i]);
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

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

int	check_extension(const char *file, const char *ext)
{
	size_t	file_len;
	size_t	ext_len;

	if (!file || !ext)
		return (0);
	file_len = ft_strlen(file);
	ext_len = ft_strlen(ext);
	if (file_len < ext_len)
		return (0);
	return (ft_strcmp(file + file_len - ext_len, ext) == 0);
}
