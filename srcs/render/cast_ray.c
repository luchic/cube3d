/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:49:35 by sruff             #+#    #+#             */
/*   Updated: 2026/04/24 18:49:38 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline t_ray	setup_initial_ray_length(t_ray origin, t_ray direction,
		t_ray map_check, t_ray ray_unit_step_size)
{
	t_ray	origin_factor;
	t_ray	ray_length;

	origin_factor = sub(origin, map_check);
	if (direction.x < 0)
	{
		ray_length.x = origin_factor.x * ray_unit_step_size.x;
	}
	else
	{
		ray_length.x = (1 - origin_factor.x) * ray_unit_step_size.x;
	}
	if (direction.y < 0)
	{
		ray_length.y = origin_factor.y * ray_unit_step_size.y;
	}
	else
	{
		ray_length.y = (1 - origin_factor.y) * ray_unit_step_size.y;
	}
	return (ray_length);
}

static int	can_prapogate(t_map *map, t_ray map_check)
{
	int	x;
	int	y;

	x = map_check.x;
	y = map_check.y;
	if (x >= map->grid_width || x < 0)
		return (0);
	if (y >= map->grid_height || y < 0)
		return (0);
	if (map->grid[y][x] == '1')
		return (0);
	return (1);
}

static inline t_casting_info	setup_hit(t_map *map, t_ray map_check,
		t_ray ray_unit_step_size, t_casting_info info)
{
	int	x;
	int	y;

	(void)ray_unit_step_size;
	x = map_check.x;
	y = map_check.y;
	info.hit = 0;
	if (x >= map->grid_width || x < 0)
		return (info);
	if (y >= map->grid_height || y < 0)
		return (info);
	if (map->grid[y][x] == '1')
		info.hit = 1;
	return (info);
}

t_casting_info	cast_ray(t_map *map, t_ray origin, t_ray direction)
{
	t_ray			map_check;
	t_ray			ray_unit_step_size;
	t_ray			step;
	t_casting_info	cast_info;

	map_check = floor_ray(origin);
	step = sign(direction);
	ray_unit_step_size.x = sqrt(1 + pow(direction.y / direction.x, 2));
	ray_unit_step_size.y = sqrt(1 + pow(direction.x / direction.y, 2));
	cast_info.length = setup_initial_ray_length(origin, direction, map_check,
			ray_unit_step_size);
	while (can_prapogate(map, map_check))
	{
		if (cast_info.length.x < cast_info.length.y)
		{
			cast_info.distanse = cast_info.length.x;
			map_check.x += step.x;
			cast_info.length.x += ray_unit_step_size.x;
			cast_info.side = 0;
		}
		else
		{
			cast_info.side = 1;
			cast_info.distanse = cast_info.length.y;
			map_check.y += step.y;
			cast_info.length.y += ray_unit_step_size.y;
		}
	}
	cast_info.hit_position.x = origin.x + direction.x * cast_info.distanse;
	cast_info.hit_position.y = origin.y + direction.y * cast_info.distanse;
	return (setup_hit(map, map_check, ray_unit_step_size, cast_info));
}
