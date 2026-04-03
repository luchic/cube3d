/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:25:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/03 13:25:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_floor_view
{
	double	ray_dir_x0;
	double	ray_dir_y0;
	double	ray_dir_x1;
	double	ray_dir_y1;
}	t_floor_view;

typedef struct s_floor_row
{
	double	row_distance;
	double	floor_step_x;
	double	floor_step_y;
	double	floor_x;
	double	floor_y;
	double	factor;
}	t_floor_row;

static int32_t	apply_distance_shading(int32_t color, double factor)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	r = (int32_t)(r / 4 + (r - r / 4) * factor);
	g = (int32_t)(g / 4 + (g - g / 4) * factor);
	b = (int32_t)(b / 4 + (b - b / 4) * factor);
	return (get_rgba(r, g, b, 255));
}

static void	init_floor_row(t_app *app, t_floor_view *view,
		t_floor_row *floor_row, int32_t y)
{
	floor_row->row_distance = (0.5 * app->window_height)
		/ (y - app->window_height / 2);
	floor_row->floor_step_x = floor_row->row_distance
		* (view->ray_dir_x1 - view->ray_dir_x0) / app->window_width;
	floor_row->floor_step_y = floor_row->row_distance
		* (view->ray_dir_y1 - view->ray_dir_y0) / app->window_width;
	floor_row->floor_x = app->player.pos_x + floor_row->row_distance
		* view->ray_dir_x0;
	floor_row->floor_y = app->player.pos_y + floor_row->row_distance
		* view->ray_dir_y0;
	floor_row->factor = (double)(y - app->window_height / 2)
		/ (app->window_height / 2);
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
		tex_x = (int32_t)(texture->width
				* (floor_row->floor_x - floor(floor_row->floor_x)))
			% (int32_t)texture->width;
		tex_y = (int32_t)(texture->height
				* (floor_row->floor_y - floor(floor_row->floor_y)))
			% (int32_t)texture->height;
		color = get_pixel(texture, tex_x, tex_y);
		color = apply_distance_shading(color, floor_row->factor);
		mlx_put_pixel(app->img->screen, x, y, color);
		floor_row->floor_x += floor_row->floor_step_x;
		floor_row->floor_y += floor_row->floor_step_y;
		x++;
	}
}

void	draw_floor(t_app *app, int32_t floor_color)
{
	mlx_texture_t	*texture;
	int32_t			y;
	t_floor_view	view;
	t_floor_row		floor_row;

	texture = app->img->txt_floor;
	if (!texture)
		return ;
	view.ray_dir_x0 = app->player.dir_x - app->player.plane_x;
	view.ray_dir_y0 = app->player.dir_y - app->player.plane_y;
	view.ray_dir_x1 = app->player.dir_x + app->player.plane_x;
	view.ray_dir_y1 = app->player.dir_y + app->player.plane_y;
	y = app->window_height / 2 + 1;
	while (y < app->window_height)
	{
		init_floor_row(app, &view, &floor_row, y);
		draw_floor_row(app, texture, &floor_row, y);
		y++;
	}
	(void)floor_color;
}
