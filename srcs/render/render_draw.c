/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:15:15 by sruff             #+#    #+#             */
/*   Updated: 2025/08/24 22:50:03 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	get_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((uint32_t)r << 24
		| (uint32_t)g << 16
		| (uint32_t)b << 8
		| (uint32_t)a);
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

	y = 0;
	while (y < app->window_height / 2)
	{
		x = 0;
		while (x < app->window_width)
		{
			mlx_put_pixel(app->img->screen, x, y, ceiling_color);
			x++;
		}
		y++;
	}
}

static void	draw_floor(t_app *app, int32_t floor_color)
{
	int32_t	x;
	int32_t	y;

	y = app->window_height / 2;
	while (y < app->window_height)
	{
		x = 0;
		while (x < app->window_width)
		{
			mlx_put_pixel(app->img->screen, x, y, floor_color);
			x++;
		}
		y++;
	}
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
