/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:58 by sruff             #+#    #+#             */
/*   Updated: 2026/04/24 18:48:42 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_radian_player(t_app *app)
{
	int	dir_x;
	int	dir_y;

	dir_x = app->player.dir_x;
	dir_y = app->player.dir_y;
	if (dir_x == 1 && dir_y == 0)
		return (0);
	else if (dir_x == 0 && dir_y == 1)
		return (M_PI / 2.0);
	else if (dir_x == -1 && dir_y == 0)
		return (M_PI);
	else if (dir_x == 0 && dir_y == -1)
		return (3 * M_PI / 2.0);
	return (0);
}

static void	init_player_direction(t_app *app)
{
	if (app->map->player_start_dir == 'N')
	{
		app->player.dir_y = -1;
		app->player.plane_x = 0.66;
	}
	else if (app->map->player_start_dir == 'S')
	{
		app->player.dir_y = 1;
		app->player.plane_x = -0.66;
	}
	else if (app->map->player_start_dir == 'E')
	{
		app->player.dir_x = 1;
		app->player.plane_y = 0.66;
	}
	else if (app->map->player_start_dir == 'W')
	{
		app->player.dir_x = -1;
		app->player.plane_y = -0.66;
	}
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
	app->player.pos_x = app->map->player_start_x + 0.5;
	app->player.pos_y = app->map->player_start_y + 0.5;
	init_player_direction(app);
	app->player.direction_radian = get_radian_player(app);
	app->player.plane_radian = app->player.direction_radian + M_PI / 2;
	app->player.origin.x = app->player.pos_x;
	app->player.origin.y = app->player.pos_y;
	app->player.radian_shifting = (FOV_DEGREE / 180.0 * M_PI) / WINDOW_WIDTH;
	setup_lenght_to_projection(app);
}
