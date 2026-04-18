/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:40:58 by sruff             #+#    #+#             */
/*   Updated: 2026/04/18 18:24:40 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_app *app, double x, double y)
{
	int32_t	map_x;
	int32_t	map_y;

	map_x = (int32_t)x;
	map_y = (int32_t)y;
	if (map_x < 0 || map_x >= app->map->grid_width || map_y < 0
		|| map_y >= app->map->grid_height)
		return (1);
	return (app->map->grid[map_y][map_x] == '1');
}

static int32_t	has_wall_padding(t_app *app, double x, double y)
{
	return (is_wall(app, x - PLAYER_RADIUS, y - PLAYER_RADIUS)
		|| is_wall(app, x + PLAYER_RADIUS, y - PLAYER_RADIUS)
		|| is_wall(app, x - PLAYER_RADIUS, y + PLAYER_RADIUS)
		|| is_wall(app, x + PLAYER_RADIUS, y + PLAYER_RADIUS));
}

void	move_forward_backward(t_app *app, double move_dir)
{
	double	new_pos_x;
	double	new_pos_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	double dir_x = cos(app->player.direction_radian);
	double dir_y = sin(app->player.direction_radian);
	new_pos_x = app->player.origin.x + dir_x * move_speed * move_dir;
	new_pos_y = app->player.origin.y + dir_y * move_speed * move_dir;
	if (!has_wall_padding(app, new_pos_x, app->player.origin.y))
		app->player.origin.x = new_pos_x;
	if (!has_wall_padding(app, app->player.origin.x, new_pos_y))
		app->player.origin.y = new_pos_y;
}

void	move_strafe(t_app *app, double strafe_dir)
{
	double	new_pos_x;
	double	new_pos_y;
	double	move_speed;
	t_ray plane = radian_to_vector(app->player.plane_radian);
	move_speed = MOVE_SPEED;
	new_pos_x = app->player.origin.x + plane.x * move_speed
		* strafe_dir;
	new_pos_y = app->player.origin.y + plane.y * move_speed
		* strafe_dir;
	if (!has_wall_padding(app, new_pos_x, app->player.origin.y))
		app->player.origin.x = new_pos_x;
	if (!has_wall_padding(app, app->player.origin.x, new_pos_y))
		app->player.origin.y = new_pos_y;
}
