/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:35:16 by stefan           #+#    #+#             */
/*   Updated: 2025/08/14 16:35:16 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_pixel(mlx_texture_t *texture, int32_t x, int32_t y)
{
	int32_t	pos;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	pos = (y * texture->width + x) * 4;
	r = texture->pixels[pos];
	g = texture->pixels[pos + 1];
	b = texture->pixels[pos + 2];
	a = texture->pixels[pos + 3];
	return (get_rgba(r, g, b, a));
}

uint32_t	get_texture_color(t_app *app, int32_t tex_num, int32_t tex_x,
		int32_t tex_y)
{
	if (tex_num == 0)
		return (get_pixel(app->img->txt_no, tex_x, tex_y));
	else if (tex_num == 1)
		return (get_pixel(app->img->txt_so, tex_x, tex_y));
	else if (tex_num == 2)
		return (get_pixel(app->img->txt_ea, tex_x, tex_y));
	else
		return (get_pixel(app->img->txt_we, tex_x, tex_y));
}

int32_t	get_texture_num(double ray_dir_x, double ray_dir_y, int32_t side)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (ray_dir_y > 0)
			return (1);
		else
			return (0);
	}
}

void	calculate_texture_params(t_app *app, t_ray_data *ray)
{
	ray->tex_num = get_texture_num(ray->ray_dir_x, ray->ray_dir_y, ray->side);
	if (ray->side == 0)
		ray->wall_x = app->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = app->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int32_t)(ray->wall_x * 64.0);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	ray->tex_step = 1.0 * 64 / ray->line_height;
	ray->tex_pos = (ray->draw_start - app->window_height / 2
			+ ray->line_height / 2) * ray->tex_step;
}
