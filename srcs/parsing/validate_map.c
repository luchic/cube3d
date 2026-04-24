/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:20:00 by sruff             #+#    #+#             */
/*   Updated: 2026/04/19 18:15:41 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_parse_error	validate_textures(t_map *map)
{
	if (!validate_texture_file(map->north_texture_path))
		return (PARSE_ERR_TEXTURE_FILE);
	if (!validate_texture_file(map->south_texture_path))
		return (PARSE_ERR_TEXTURE_FILE);
	if (!validate_texture_file(map->west_texture_path))
		return (PARSE_ERR_TEXTURE_FILE);
	if (!validate_texture_file(map->east_texture_path))
		return (PARSE_ERR_TEXTURE_FILE);
	return (PARSE_SUCCESS);
}

static t_parse_error	check_enclosed(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->grid_height)
	{
		x = -1;
		while (++x < map->grid_width)
		{
			if (ft_strchr("0NSEW", map->grid[y][x]))
			{
				if (x == 0 || x == map->grid_width - 1
					|| y == 0 || y == map->grid_height - 1)
					return (PARSE_ERR_MAP_NOT_ENCLOSED);
				if (map->grid[y][x + 1] == ' ' || map->grid[y][x - 1] == ' '
					|| map->grid[y + 1][x] == ' ' || map->grid[y - 1][x] == ' ')
					return (PARSE_ERR_MAP_NOT_ENCLOSED);
			}
		}
	}
	return (PARSE_SUCCESS);
}

static t_parse_error	check_map_chars(t_map *map, int *players)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->grid_height)
	{
		x = -1;
		while (++x < map->grid_width)
		{
			if (!ft_strchr("01NSEW ", map->grid[y][x]))
				return (PARSE_ERR_INVALID_MAP_CHAR);
			if (ft_strchr("NSEW", map->grid[y][x]))
			{
				(*players)++;
				map->player_start_x = x;
				map->player_start_y = y;
				map->player_start_dir = map->grid[y][x];
			}
		}
	}
	return (PARSE_SUCCESS);
}

t_parse_error	validate_map(t_map *map)
{
	int				players;
	t_parse_error	err;

	players = 0;
	err = check_map_chars(map, &players);
	if (err != PARSE_SUCCESS)
		return (err);
	if (players != 1)
		return (PARSE_ERR_INVALID_PLAYER_COUNT);
	err = validate_textures(map);
	if (err != PARSE_SUCCESS)
		return (err);
	return (check_enclosed(map));
}