/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:20:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/25 12:23:50 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_graphics(t_app *app)
{
	if (!app)
		return ;
	clean_frames(app);
	if (app->img)
		cleanup_textures(app->img);
	if (app->mlx)
		mlx_terminate(app->mlx);
}

void	setup_graphics(t_app *app)
{
	app->window_width = WINDOW_WIDTH;
	app->window_height = WINDOW_HEIGHT;
	app->mlx = mlx_init(app->window_width, app->window_height, APP_TITLE, true);
	if (!app->mlx)
	{
		exit_with_error("MLX initialization failed.", app);
	}
	if (!load_textures(app))
	{
		exit_with_error("Failed to load west texture.", app);
	}
	if (!init_frames(app))
	{
		exit_with_error("Failed to load west texture.", app);
	}
	draw_background(app);
}
