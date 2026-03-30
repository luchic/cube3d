/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:22:46 by sruff             #+#    #+#             */
/*   Updated: 2026/03/30 11:11:16 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

const char	*get_parse_error_message(t_parse_error error)
{
	if (error == PARSE_ERR_INVALID_EXTENSION)
		return ("Map file must have a .cub extension.");
	if (error == PARSE_ERR_OPEN_FILE)
		return ("Could not open map file.");
	if (error == PARSE_ERR_ALLOC)
		return ("Memory allocation failed during parsing.");
	if (error == PARSE_ERR_MISSING_ELEMENTS)
		return ("Missing one or more map elements.");
	if (error == PARSE_ERR_MAP_GRID_NOT_FOUND)
		return ("Map grid not found in file.");
	if (error == PARSE_ERR_EMPTY_LINE_IN_MAP)
		return ("Empty line found in map section.");
	if (error == PARSE_ERR_INVALID_LINE || error == PARSE_NO_MATCH)
		return ("Invalid line or missing elements before map grid.");
	if (error == PARSE_ERR_DUPLICATE_TEXTURE)
		return ("Duplicate texture definition.");
	if (error == PARSE_ERR_TEXTURE_FILE)
		return ("Texture file not found or inaccessible.");
	if (error == PARSE_ERR_DUPLICATE_COLOR)
		return ("Duplicate color definition.");
	if (error == PARSE_ERR_INVALID_RGB)
		return ("Invalid RGB color format.");
	if (error == PARSE_ERR_INVALID_MAP_CHAR)
		return ("Invalid character in map grid.");
	if (error == PARSE_ERR_INVALID_PLAYER_COUNT)
		return ("Map must have exactly one player start position.");
	if (error == PARSE_ERR_MAP_NOT_ENCLOSED)
		return ("Map is not enclosed by walls.");
	return ("Unknown parse error.");
}

void	exit_with_error(const char *message, t_app *app)
{
	ft_printf("Error: %s\n", message);
	if (app)
	{
		if (app->image)
			mlx_delete_image(app->mlx, app->image);
		if (app->mlx)
			mlx_terminate(app->mlx);
	}
	ft_clean();
	exit(1);
}
