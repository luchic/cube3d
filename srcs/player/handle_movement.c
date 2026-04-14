/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:17:10 by sruff             #+#    #+#             */
/*   Updated: 2026/04/05 12:06:01 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	rot_speed = ROTATE_SPPED;
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
