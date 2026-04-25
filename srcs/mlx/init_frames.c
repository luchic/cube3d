/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_frames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:10:43 by sruff             #+#    #+#             */
/*   Updated: 2026/04/25 15:10:55 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_frames(t_app *app)
{
	if (!app)
		return ;
	if (app->frames.floor_frame)
	{
		mlx_delete_image(app->mlx, app->frames.floor_frame);
		app->frames.floor_frame = NULL;
	}
	if (app->frames.sky_frame)
	{
		mlx_delete_image(app->mlx, app->frames.sky_frame);
		app->frames.sky_frame = NULL;
	}
	if (app->frames.tools_frame)
	{
		mlx_delete_image(app->mlx, app->frames.tools_frame);
		app->frames.tools_frame = NULL;
	}
	if (app->frames.walls_frame)
	{
		mlx_delete_image(app->mlx, app->frames.walls_frame);
		app->frames.walls_frame = NULL;
	}
}

static int	frame_is_allocated(t_app *app)
{
	return (app->frames.floor_frame != NULL && app->frames.sky_frame != NULL
		&& app->frames.tools_frame != NULL && app->frames.walls_frame != NULL);
}

int	init_frames(t_app *app)
{
	app->frames.sky_frame = mlx_new_image(app->mlx, app->window_width,
			app->window_height);
	app->frames.floor_frame = mlx_new_image(app->mlx, app->window_width,
			app->window_height);
	app->frames.walls_frame = mlx_new_image(app->mlx, app->window_width,
			app->window_height);
	app->frames.tools_frame = mlx_new_image(app->mlx, app->window_width,
			app->window_height);
	if (!frame_is_allocated(app))
	{
		clean_frames(app);
		return (0);
	}
	mlx_image_to_window(app->mlx, app->frames.sky_frame, 0, 0);
	mlx_image_to_window(app->mlx, app->frames.floor_frame, 0, 0);
	mlx_image_to_window(app->mlx, app->frames.walls_frame, 0, 0);
	mlx_image_to_window(app->mlx, app->frames.tools_frame, 0, 0);
	return (1);
}
