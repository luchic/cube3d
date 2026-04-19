/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:20:00 by sruff             #+#    #+#             */
/*   Updated: 2026/04/17 12:20:00 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static int	is_walkable(char c)
{
	return (c == '0' || is_player(c));
}

static t_parse_error	check_enclosed(t_map *map, int y, int x)
{
	if (y == 0 || y == map->grid_height - 1 || x == 0 || x == map->grid_width - 1)
		return (PARSE_ERR_MAP_NOT_ENCLOSED);
	if (map->grid[y - 1][x] == ' ' || map->grid[y + 1][x] == ' '
		|| map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' ')
		return (PARSE_ERR_MAP_NOT_ENCLOSED);
	return (PARSE_SUCCESS);
}

t_parse_error	validate_map(t_map *map)
{
	int	y;
	int	x;
	int	players;

	players = 0;
	y = 0;
	while (y < map->grid_height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (!ft_strchr("01 NSEW", map->grid[y][x]))
				return (PARSE_ERR_INVALID_MAP_CHAR);
			if (is_player(map->grid[y][x]))
			{
				players++;
				map->player_start_x = x;
				map->player_start_y = y;
				map->player_start_dir = map->grid[y][x];
			}
			if (is_walkable(map->grid[y][x]))
			{
				if (check_enclosed(map, y, x) != PARSE_SUCCESS)
					return (PARSE_ERR_MAP_NOT_ENCLOSED);
			}
			x++;
		}
		y++;
	}
	if (players != 1)
		return (PARSE_ERR_INVALID_PLAYER_COUNT);
	return (PARSE_SUCCESS);
}

t_parse_error	pad_grid(t_map *map)
{
	char	**new_grid;
	int		y;
	int		x;

	new_grid = ft_calloc(map->grid_height + 1, sizeof(char *));
	if (!new_grid)
		return (PARSE_ERR_ALLOC);
	y = 0;
	while (y < map->grid_height)
	{
		new_grid[y] = ft_calloc(map->grid_width + 1, sizeof(char));
		if (!new_grid[y])
			return (PARSE_ERR_ALLOC);
		ft_memset(new_grid[y], ' ', map->grid_width);
		x = 0;
		while (map->grid[y][x])
		{
			new_grid[y][x] = map->grid[y][x];
			x++;
		}
		y++;
	}
	// Free old grid nodes (not contents if we reuse, but here we replace everything)
	// For simplicity, assuming caller handles or we leak for now until full GC.
	map->grid = new_grid;
	return (PARSE_SUCCESS);
}
