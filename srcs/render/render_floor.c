/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:25:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/24 14:36:10 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_floor_row(t_app *app, t_floor_view *view,
		t_floor_row *floor_row, int32_t y)
{
	floor_row->row_distance = (app->player.len_to_screen * TILE_SIZE_DOUBLE
				/ 2.0) / (y - app->window_height / 2.0);
	floor_row->floor_setp.x = floor_row->row_distance * (view->ray_dir1.x
			- view->ray_dir0.x) / app->window_width;
	floor_row->floor_setp.y = floor_row->row_distance * (view->ray_dir1.y
			- view->ray_dir0.y) / app->window_width;
	floor_row->floor_pos.x = app->player.origin.x + floor_row->row_distance
		* view->ray_dir0.x;
	floor_row->floor_pos.y = app->player.origin.y + floor_row->row_distance
		* view->ray_dir0.y;
	floor_row->factor = (double)(y - app->window_height / 2)
		/ (app->window_height / 2);
}

static int32_t	apply_distance_shading(int32_t color, double factor)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	r = (int32_t)((r >> 2) + (r - (r >> 4)) * factor);
	g = (int32_t)((g >> 2) + (g - (g >> 4)) * factor);
	b = (int32_t)((b >> 2) + (b - (b >> 4)) * factor);
	return (get_rgba(r, g, b, 255));
}

static void	draw_floor_row(t_app *app, mlx_texture_t *texture,
		t_floor_row *floor_row, int32_t y)
{
	int32_t	x;
	int32_t	tex_x;
	int32_t	tex_y;
	int32_t	color;

	x = 0;
	while (x < app->window_width)
	{
		tex_x = (int32_t)(texture->width * (floor_row->floor_pos.x
					- floor(floor_row->floor_pos.x))) % (int32_t)texture->width;
		tex_y = (int32_t)(texture->height * (floor_row->floor_pos.y
					- floor(floor_row->floor_pos.y))) % (int32_t)texture->height;
		color = get_pixel(texture, tex_x, tex_y);
		color = apply_distance_shading(color, floor_row->factor);
		mlx_put_pixel(app->frames.floor_frame, x, y, color);
		floor_row->floor_pos.x += floor_row->floor_setp.x;
		floor_row->floor_pos.y += floor_row->floor_setp.y;
		x++;
	}
}

void	draw_floor(t_app *app)
{
	t_ray			player_direction;
	t_ray			player_plane;
	int32_t			y;
	t_floor_view	view;
	t_floor_row		floor_row;

	if (!app->img->txt_floor)
		return ;
	player_direction = radian_to_vector(app->player.direction_radian);
	player_plane = radian_to_vector(app->player.plane_radian);
	player_plane.x *= tan((FOV_DEGREE / 2) * M_PI / 180);
	player_plane.y *= tan((FOV_DEGREE / 2) * M_PI / 180);
	view.ray_dir0.x = player_direction.x - player_plane.x;
	view.ray_dir0.y = player_direction.y - player_plane.y;
	view.ray_dir1.x = player_direction.x + player_plane.x;
	view.ray_dir1.y = player_direction.y + player_plane.y;
	y = app->window_height / 2 + 1;
	while (y < app->window_height)
	{
		init_floor_row(app, &view, &floor_row, y);
		draw_floor_row(app, app->img->txt_floor, &floor_row, y);
		y++;
	}
}
