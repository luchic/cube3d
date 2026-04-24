/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:20:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/24 18:41:13 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_sky(t_app *app)
{
	int32_t	ceiling_color;

	ceiling_color = get_rgba(app->map->ceiling_color[0],
			app->map->ceiling_color[1], app->map->ceiling_color[2], 255);
	draw_sky(app, ceiling_color);
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
	mlx_image_to_window(app->mlx, app->frames.sky_frame, 0, 0);
	mlx_image_to_window(app->mlx, app->frames.floor_frame, 0, 0);
	mlx_image_to_window(app->mlx, app->frames.walls_frame, 0, 0);
	mlx_image_to_window(app->mlx, app->frames.tools_frame, 0, 0);
	return (1);
}

void	cleanup_graphics(t_app *app)
{
	if (!app)
		return ;
	if (app->mlx)
		mlx_terminate(app->mlx);
}

void	setup_graphics(t_app *app)
{
	int	ceiling_color;

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
	init_frames(app);
	ceiling_color = get_rgba(app->map->ceiling_color[0],
			app->map->ceiling_color[1], app->map->ceiling_color[2], 255);
	draw_sky(app, ceiling_color);
	init_sky(app);
}
