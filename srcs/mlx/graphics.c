/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:20:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/25 12:18:33 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_background(t_app *app)
{
	int32_t	ceiling_color;
	int32_t	floor_color;

	ceiling_color = get_rgba(app->map->ceiling_color[0],
			app->map->ceiling_color[1], app->map->ceiling_color[2], 255);
	floor_color = get_rgba(app->map->floor_color[0],
			app->map->floor_color[1], app->map->floor_color[2], 255);
	draw_sky(app, ceiling_color);
	draw_floor(app, floor_color);
}

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
	init_background(app);
}
