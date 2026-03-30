/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:17:10 by sruff             #+#    #+#             */
/*   Updated: 2025/08/24 21:43:25 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	is_wall(t_app *app, double x, double y)
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

static void	rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(angle) - player->plane_y
		* sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}

static void	handle_rotation(t_app *app)
{
	double	rot_speed;

	rot_speed = MOVE_SPEED * 0.7;
	if (app->keys[4])
	{
		rotate_player(&app->player, -rot_speed);
	}
	if (app->keys[5])
	{
		rotate_player(&app->player, rot_speed);
	}
}

void	handle_movement(t_app *app)
{
	handle_rotation(app);
	if (app->keys[0])
		move_forward_backward(app, 1.0);
	if (app->keys[1])
		move_forward_backward(app, -1.0);
	if (app->keys[2])
		move_strafe(app, -1.0);
	if (app->keys[3])
		move_strafe(app, 1.0);
}
