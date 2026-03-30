/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:35:37 by stefan           #+#    #+#             */
/*   Updated: 2025/08/14 16:35:37 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_wall_params(t_app *app, t_ray_data *ray)
{
	double	raw_height;
	int32_t	half;

	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - app->player.pos_x + (1
					- ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - app->player.pos_y + (1
					- ray->step_y) / 2) / ray->ray_dir_y;
	raw_height = app->window_height / ray->perp_wall_dist;
	if (raw_height > INT32_MAX)
		raw_height = INT32_MAX;
	ray->line_height = (int32_t)raw_height;
	half = ray->line_height / 2;
	ray->draw_start = app->window_height / 2 - half;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = app->window_height / 2 + half;
	if (ray->draw_end >= app->window_height)
		ray->draw_end = app->window_height - 1;
}

void	draw_vertical_strip(t_app *app, int32_t x, t_ray_data *ray)
{
	int32_t		y;
	int32_t		tex_y;
	uint32_t	color;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int32_t)ray->tex_pos & (64 - 1);
		ray->tex_pos += ray->tex_step;
		color = get_texture_color(app, ray->tex_num, ray->tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		mlx_put_pixel(app->img->screen, x, y, color);
		y++;
	}
}

void	calculate_and_draw_wall(t_app *app, int32_t x, t_ray_data *ray_data)
{
	calculate_wall_params(app, ray_data);
	calculate_texture_params(app, ray_data);
	draw_vertical_strip(app, x, ray_data);
}
