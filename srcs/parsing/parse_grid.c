/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 17:14:40 by stefan            #+#    #+#             */
/*   Updated: 2026/04/17 17:14:41 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3d.h"

static t_parse_error	add_line_to_grid(t_map *map, char *line)
{
	char	**new_grid;
	int		i;
	int		len;

	new_grid = ft_malloc(sizeof(char *) * (map->grid_height + 2));
	if (!new_grid)
		return (PARSE_ERR_ALLOC);
	i = -1;
	while (++i < map->grid_height)
		new_grid[i] = map->grid[i];
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[--len] = '\0';
	new_grid[i] = malloc_strdup(line);
	if (!new_grid[i])
		return (PARSE_ERR_ALLOC);
	new_grid[i + 1] = NULL;
	map->grid = new_grid;
	map->grid_height++;
	if (len > map->grid_width)
		map->grid_width = len;
	return (PARSE_SUCCESS);
}

t_parse_error	pad_grid(t_map *map)
{
	int		i;
	char	*new_line;
	int		len;

	i = -1;
	while (++i < map->grid_height)
	{
		len = ft_strlen(map->grid[i]);
		if (len < map->grid_width)
		{
			new_line = ft_malloc(map->grid_width + 1);
			if (!new_line)
				return (PARSE_ERR_ALLOC);
			ft_memset(new_line, ' ', map->grid_width);
			ft_memcpy(new_line, map->grid[i], len);
			new_line[map->grid_width] = '\0';
			map->grid[i] = new_line;
		}
	}
	return (PARSE_SUCCESS);
}

t_parse_error	parse_grid(t_parse_ctx *ctx, char *first_line)
{
	char			*line;
	t_parse_error	err;
	bool			empty_line_found;

	err = add_line_to_grid(ctx->map, first_line);
	if (err != PARSE_SUCCESS)
		return (err);
	empty_line_found = false;
	while (1)
	{
		line = get_next_line(ctx->fd);
		if (!line)
			break ;
		if (is_empty_line(line))
			empty_line_found = true;
		else
		{
			if (empty_line_found)
				return (PARSE_ERR_EMPTY_LINE_IN_MAP);
			err = add_line_to_grid(ctx->map, line);
			if (err != PARSE_SUCCESS)
				return (err);
		}
	}
	return (pad_grid(ctx->map));
}
