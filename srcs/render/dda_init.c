/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:36:53 by stefan           #+#    #+#             */
/*   Updated: 2025/08/24 22:36:53 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_dda_x_axis(t_app *app, t_ray_data *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (app->player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - app->player.pos_x)
			* ray->delta_dist_x;
	}
}

static void	init_dda_y_axis(t_app *app, t_ray_data *ray)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (app->player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - app->player.pos_y)
			* ray->delta_dist_y;
	}
}

void	init_dda(t_app *app, t_ray_data *ray)
{
	ray->map_x = (int32_t)app->player.pos_x;
	ray->map_y = (int32_t)app->player.pos_y;
	init_dda_x_axis(app, ray);
	init_dda_y_axis(app, ray);
}
