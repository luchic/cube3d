/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_map_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:49:31 by sruff             #+#    #+#             */
/*   Updated: 2025/08/24 14:00:21 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int32_t	find_max_grid_width(t_map *map)
{
	int32_t	i;
	int32_t	current_len;
	int32_t	max_width;

	max_width = 0;
	i = -1;
	while (++i < map->grid_height)
	{
		current_len = ft_strlen(map->grid[i]);
		if (map->grid[i][current_len - 1] == '\n')
		{
			map->grid[i][current_len - 1] = '\0';
			current_len--;
		}
		if (current_len > max_width)
			max_width = current_len;
	}
	return (max_width);
}

t_parse_error	pad_map_grid(t_app *app)
{
	int32_t	i;
	t_map	*map;

	map = app->map;
	map->grid_width = find_max_grid_width(map);
	i = -1;
	while (++i < map->grid_height)
	{
		if (pad_map_line(map, i) != PARSE_SUCCESS)
			return (PARSE_ERR_ALLOC);
	}
	(void)app;
	return (PARSE_SUCCESS);
}
