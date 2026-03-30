/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:57:55 by sruff             #+#    #+#             */
/*   Updated: 2025/08/24 16:22:29 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	init_player(t_app *app)
{
	ft_memset(&app->player, 0, sizeof(t_player));
	app->player.pos_x = app->map->player_start_x + 0.5;
	app->player.pos_y = app->map->player_start_y + 0.5;
	init_player_direction(app);
}
