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

static t_parse_error	validate_character(t_app *app, int32_t x, int32_t y,
		int32_t *player_count)
{
	char	c;
	t_map	*map;

	map = app->map;
	c = map->grid[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*player_count > 0)
			return (PARSE_ERR_INVALID_PLAYER_COUNT);
		map->player_start_x = x;
		map->player_start_y = y;
		map->player_start_dir = c;
		(*player_count)++;
	}
	else if (c != '0' && c != '1' && c != ' ')
		return (PARSE_ERR_INVALID_MAP_CHAR);
	return (PARSE_SUCCESS);
}

static t_parse_error	check_map_characters(t_app *app)
{
	int32_t			player_count;
	int32_t			y;
	int32_t			x;
	t_map			*map;
	t_parse_error	error;

	map = app->map;
	player_count = 0;
	y = -1;
	while (++y < map->grid_height)
	{
		x = -1;
		while (++x < map->grid_width)
		{
			error = validate_character(app, x, y, &player_count);
			if (error != PARSE_SUCCESS)
				return (error);
		}
	}
	if (player_count != 1)
		return (PARSE_ERR_INVALID_PLAYER_COUNT);
	return (PARSE_SUCCESS);
}

static t_parse_error	check_elements_present(t_app *app)
{
	int32_t	i;

	i = -1;
	while (++i < ELEMENT_COUNT)
	{
		if (!app->map->elements_found[i])
			return (PARSE_ERR_MISSING_ELEMENTS);
	}
	return (PARSE_SUCCESS);
}

t_parse_error	validate_map(t_app *app)
{
	t_parse_error	error;

	error = check_elements_present(app);
	if (error != PARSE_SUCCESS)
		return (error);
	error = check_map_characters(app);
	if (error != PARSE_SUCCESS)
		return (error);
	return (check_walls_enclosed(app));
}
