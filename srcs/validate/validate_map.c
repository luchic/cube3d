/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:53:09 by sruff             #+#    #+#             */
/*   Updated: 2025/08/24 16:38:40 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_character(t_app *app, int32_t x, int32_t y,
		int32_t *player_count)
{
	char	c;
	t_map	*map;

	map = app->map;
	c = map->grid[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*player_count > 0)
			exit_with_error("Multiple player starts defined.", app);
		map->player_start_x = x;
		map->player_start_y = y;
		map->player_start_dir = c;
		(*player_count)++;
	}
	else if (c != '0' && c != '1' && c != ' ')
		exit_with_error("Invalid character in map grid.", app);
}

static void	check_map_characters(t_app *app)
{
	int32_t	player_count;
	int32_t	y;
	int32_t	x;
	t_map	*map;

	map = app->map;
	player_count = 0;
	y = -1;
	while (++y < map->grid_height)
	{
		x = -1;
		while (++x < map->grid_width)
		{
			validate_character(app, x, y, &player_count);
		}
	}
	if (player_count != 1)
		exit_with_error("Map must have exactly one player start position.",
			app);
}

static void	check_elements_present(t_app *app)
{
	int32_t	i;

	i = -1;
	while (++i < ELEMENT_COUNT)
	{
		if (!app->map->elements_found[i])
			exit_with_error("Missing one or more map elements.", app);
	}
}

void	validate_map(t_app *app)
{
	check_elements_present(app);
	check_map_characters(app);
	check_walls_enclosed(app);
}
