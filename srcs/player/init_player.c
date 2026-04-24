/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:58 by sruff             #+#    #+#             */
/*   Updated: 2026/04/24 21:24:43 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player_direction(t_app *app)
{
	if (app->map->player_start_dir == 'N')
	{
		app->player.direction_radian = 3 * M_PI / 2.0;
	}
	else if (app->map->player_start_dir == 'S')
	{
		app->player.direction_radian = M_PI / 2.0;
	}
	else if (app->map->player_start_dir == 'E')
	{
		app->player.direction_radian = 0;
	}
	else if (app->map->player_start_dir == 'W')
	{
		app->player.direction_radian = M_PI;
	}
	else
	{
		app->player.direction_radian = 0;
	}
	app->player.plane_radian = app->player.direction_radian + M_PI / 2;
}

void	setup_lenght_to_projection(t_app *app)
{
	double	lenght_to_screen;
	double	radian;

	radian = FOV_DEGREE / 360.0 * M_PI; // (fov / 2) / 180 * PI
	lenght_to_screen = (WINDOW_WIDTH / 2.0) / tan(radian);
	app->player.len_to_screen = lenght_to_screen / TILE_SIZE_DOUBLE;
}

void	init_player(t_app *app)
{
	ft_memset(&app->player, 0, sizeof(t_player));
	init_player_direction(app);
	app->player.origin.x = app->map->player_start_x + 0.5;
	app->player.origin.y = app->map->player_start_x + 0.5;
	app->player.radian_shifting = (FOV_DEGREE / 180.0 * M_PI) / WINDOW_WIDTH;
	setup_lenght_to_projection(app);
}
