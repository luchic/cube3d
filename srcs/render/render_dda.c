/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_dda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:34:56 by stefan           #+#    #+#             */
/*   Updated: 2025/08/14 16:34:56 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	step_one_cell(t_ray_data *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

static int32_t	is_oob(const t_app *app, const t_ray_data *ray)
{
	return (ray->map_x < 0 || ray->map_y < 0
		|| ray->map_x >= app->map->grid_width
		|| ray->map_y >= app->map->grid_height);
}

void	execute_dda(t_app *app, t_ray_data *ray)
{
	while (ray->hit == 0)
	{
		step_one_cell(ray);
		if (is_oob(app, ray))
			break ;
		if (app->map->grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}
