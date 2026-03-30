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

void	pad_map_grid(t_app *app)
{
	int32_t		i;
	int32_t		len;
	char		*new_line;
	t_map		*map;
	int32_t		j;

	map = app->map;
	map->grid_width = find_max_grid_width(map);
	i = -1;
	while (++i < map->grid_height)
	{
		len = ft_strlen(map->grid[i]);
		if (len < map->grid_width)
		{
			new_line = ft_malloc(map->grid_width + 1);
			if (!new_line)
				exit_with_error("Memory allocation failed for padding.", app);
			ft_memcpy(new_line, map->grid[i], len);
			j = len;
			while (j < map->grid_width)
				new_line[j++] = ' ';
			new_line[map->grid_width] = '\0';
			map->grid[i] = new_line;
		}
	}
}
