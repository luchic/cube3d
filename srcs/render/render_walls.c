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

t_casting_info	start_casting(t_app *app, int x)
{
	double			plane_scale;
	double			beta;
	t_ray			direction;
	t_ray			plane;
	t_casting_info	info;

	direction = radian_to_vector(app->player.direction_radian);
	plane = radian_to_vector(app->player.plane_radian);
	plane_scale = 2.0 * x / (double)app->window_width - 1.0;
	plane.x *= (plane_scale * tan((FOV_DEGREE / 2.0) * M_PI / 180.0));
	plane.y *= (plane_scale * tan((FOV_DEGREE / 2.0) * M_PI / 180.0));
	direction.x += plane.x;
	direction.y += plane.y;
	info = cast_ray(app->map, app->player.origin, direction);
	beta = ((double)x - (double)app->window_width / 2)
		* app->player.radian_shifting;
	info.distanse = info.distanse * cos(beta);
	return (info);
}

void	render_walls(t_app *app)
{
	int32_t			x;
	t_casting_info	info;

	x = 0;
	clean_wall_frame(app->frames.walls_frame);
	while (x < app->window_width)
	{
		info = start_casting(app, x);
		if (info.hit)
		{
			draw_wertical_line(app, info, x);
		}
		x++;
	}
}
