/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:40:58 by sruff             #+#    #+#             */
/*   Updated: 2025/08/24 21:46:20 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward_backward(t_app *app, double move_dir)
{
	double	new_pos_x;
	double	new_pos_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	new_pos_x = app->player.pos_x + app->player.dir_x * move_speed * move_dir;
	new_pos_y = app->player.pos_y + app->player.dir_y * move_speed * move_dir;
	if (!is_wall(app, new_pos_x, app->player.pos_y))
		app->player.pos_x = new_pos_x;
	if (!is_wall(app, app->player.pos_x, new_pos_y))
		app->player.pos_y = new_pos_y;
}

void	move_strafe(t_app *app, double strafe_dir)
{
	double	new_pos_x;
	double	new_pos_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	new_pos_x = app->player.pos_x + app->player.plane_x * move_speed
		* strafe_dir;
	new_pos_y = app->player.pos_y + app->player.plane_y * move_speed
		* strafe_dir;
	if (!is_wall(app, new_pos_x, app->player.pos_y))
		app->player.pos_x = new_pos_x;
	if (!is_wall(app, app->player.pos_x, new_pos_y))
		app->player.pos_y = new_pos_y;
}
