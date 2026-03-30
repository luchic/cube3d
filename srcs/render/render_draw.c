/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:15:15 by sruff             #+#    #+#             */
/*   Updated: 2026/03/30 13:43:52 by nluchini         ###   ########.fr       */
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

int32_t	get_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((uint32_t)r << 24
		| (uint32_t)g << 16
		| (uint32_t)b << 8
		| (uint32_t)a);
}

static int32_t	interpolate_channel(int32_t start, int32_t end, double factor)
{
	return ((int32_t)(start + (end - start) * factor));
}

static int32_t	get_gradient_color(int32_t base_color, double factor)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;

	r = (base_color >> 24) & 0xFF;
	g = (base_color >> 16) & 0xFF;
	b = (base_color >> 8) & 0xFF;
	r = interpolate_channel(r / 3, r, factor);
	g = interpolate_channel(g / 3, g, factor);
	b = interpolate_channel(b / 3, b, factor);
	return (get_rgba(r, g, b, 255));
}

static int32_t	apply_distance_shading(int32_t color, double factor)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	r = interpolate_channel(r / 4, r, factor);
	g = interpolate_channel(g / 4, g, factor);
	b = interpolate_channel(b / 4, b, factor);
	return (get_rgba(r, g, b, 255));
}

static double	get_floor_shading_factor(t_app *app, int32_t y)
{
	return ((double)(y - app->window_height / 2) / (app->window_height / 2));
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
	floor_row->factor = get_floor_shading_factor(app, y);
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

void	cast_rays(t_app *app)
{
	int32_t		x;
	t_ray_data	ray_data;

	x = 0;
	while (x < app->window_width)
	{
		process_ray(app, x, &ray_data);
		x++;
	}
}

static void	draw_ceiling(t_app *app, int32_t ceiling_color)
{
	int32_t	x;
	int32_t	y;
	double	factor;
	int32_t	shaded_color;

	y = 0;
	while (y < app->window_height / 2)
	{
		factor = (double)y / (app->window_height / 2);
		shaded_color = get_gradient_color(ceiling_color, factor);
		x = 0;
		while (x < app->window_width)
		{
			mlx_put_pixel(app->img->screen, x, y, shaded_color);
			x++;
		}
		y++;
	}
}

//INFO: shading implemented in simple way, i'm assume that horizont always
//in the middle of screan. It mean we need to rebuild calculation 
//if we want to move our camera up
static void	draw_floor(t_app *app, int32_t floor_color)
{
	mlx_texture_t	*texture;
	int32_t	y;
	t_floor_view	view;
	t_floor_row	floor_row;

	texture = app->img->txt_floor;
	if (!texture)
		return ;
	view.ray_dir_x0 = app->player.dir_x - app->player.plane_x;
	view.ray_dir_y0 = app->player.dir_y - app->player.plane_y;
	view.ray_dir_x1 = app->player.dir_x + app->player.plane_x;
	view.ray_dir_y1 = app->player.dir_y + app->player.plane_y;
	y = app->window_height / 2;
	while (y < app->window_height)
	{
		if (y == app->window_height / 2)
		{
			y++;
			continue ;
		}
		init_floor_row(app, &view, &floor_row, y);
		draw_floor_row(app, texture, &floor_row, y);
		y++;
	}
	(void)floor_color;
}

void	draw_frame(t_app *app)
{
	int32_t	ceiling_color;
	int32_t	floor_color;

	if (!app || !app->img || !app->img->screen)
		return ;
	ceiling_color = get_rgba(app->map->ceiling_color[0],
			app->map->ceiling_color[1], app->map->ceiling_color[2], 255);
	floor_color = get_rgba(app->map->floor_color[0], app->map->floor_color[1],
			app->map->floor_color[2], 255);
	draw_ceiling(app, ceiling_color);
	draw_floor(app, floor_color);
	cast_rays(app);
}
