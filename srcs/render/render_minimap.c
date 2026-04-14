/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 18:08:23 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/05 18:08:27 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	get_tile_color(char tile)
{
	if (tile == '1')
		return (get_rgba(235, 235, 235, 255));
	if (tile == '0' || tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		return (get_rgba(75, 75, 75, 255));
	return (0);
}

static void	draw_map_tile(t_app *app, t_point center, t_point map_pos,
		t_minimap_style style)
{
	t_point		tile;
	uint32_t	color;

	color = get_tile_color(app->map->grid[map_pos.y][map_pos.x]);
	if (color == 0)
		return ;
	tile.x = center.x + (int32_t)round((map_pos.x - app->player.pos_x)
			* MINIMAP_TILE_SIZE);
	tile.y = center.y + (int32_t)round((map_pos.y - app->player.pos_y)
			* MINIMAP_TILE_SIZE);
	style.color = color;
	draw_rect(app, tile, MINIMAP_TILE_SIZE, style);
}

static void	draw_map_tiles(t_app *app, t_point center, t_minimap_style style)
{
	t_point		map_pos;

	map_pos.y = 0;
	while (map_pos.y < app->map->grid_height)
	{
		map_pos.x = 0;
		while (map_pos.x < app->map->grid_width)
		{
			draw_map_tile(app, center, map_pos, style);
			map_pos.x++;
		}
		map_pos.y++;
	}
}

static void	draw_minimap_frame(t_app *app, int32_t panel_size)
{
	int32_t	x;
	int32_t	y;
	t_point	point;

	y = 0;
	while (y < panel_size)
	{
		x = 0;
		while (x < panel_size)
		{
			point.x = MINIMAP_MARGIN + x;
			point.y = MINIMAP_MARGIN + y;
			if (x < 2 || y < 2 || x >= panel_size - 2 || y >= panel_size - 2)
				put_pixel_safe_screen(app, point, get_rgba(255, 255, 255, 255));
			else
				put_pixel_safe_screen(app, point, get_rgba(20, 20, 20, 255));
			x++;
		}
		y++;
	}
}

void	render_minimap(t_app *app)
{
	t_minimap_style	style;
	t_point			center;
	t_point			player;
	t_point			direction;

	if (!app || !app->map || !app->img || !app->img->screen)
		return ;
	style.panel_size = MINIMAP_VISIBLE_TILES * MINIMAP_TILE_SIZE + 4;
	draw_minimap_frame(app, style.panel_size);
	center.x = MINIMAP_MARGIN + style.panel_size / 2;
	center.y = MINIMAP_MARGIN + style.panel_size / 2;
	draw_map_tiles(app, center, style);
	player.x = center.x - MINIMAP_PLAYER_SIZE / 2;
	player.y = center.y - MINIMAP_PLAYER_SIZE / 2;
	style.color = get_rgba(255, 80, 80, 255);
	draw_rect(app, player, MINIMAP_PLAYER_SIZE, style);
	direction.x = center.x + (int32_t)round(app->player.dir_x
			* MINIMAP_DIRECTION_SIZE);
	direction.y = center.y + (int32_t)round(app->player.dir_y
			* MINIMAP_DIRECTION_SIZE);
	draw_line(app, center, direction, style);
}
