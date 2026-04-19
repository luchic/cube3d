/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:20:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/19 15:32:53 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_frames(t_app *app)
{
	app->frames.sky_frame = mlx_new_image(app->mlx, app->window_width, app->window_height);
	app->frames.floor_frame = mlx_new_image(app->mlx, app->window_width, app->window_height);
	app->frames.walls_frame = mlx_new_image(app->mlx, app->window_width, app->window_height);
	app->frames.tools_frame = mlx_new_image(app->mlx, app->window_width, app->window_height);

	mlx_image_to_window(app->mlx, app->frames.sky_frame, 0, 0);
	mlx_image_to_window(app->mlx, app->frames.floor_frame, 0, 0);
	mlx_image_to_window(app->mlx, app->frames.walls_frame, 0, 0);
	mlx_image_to_window(app->mlx, app->frames.tools_frame, 0, 0);

	return (1);
}

void	cleanup_textures(t_images *img)
{
	if (!img)
		return ;
	if (img->txt_no)
		mlx_delete_texture(img->txt_no);
	if (img->txt_so)
		mlx_delete_texture(img->txt_so);
	if (img->txt_ea)
		mlx_delete_texture(img->txt_ea);
	if (img->txt_we)
		mlx_delete_texture(img->txt_we);
	if (img->txt_floor)
		mlx_delete_texture(img->txt_floor);
}

void	cleanup_graphics(t_app *app)
{
	if (!app)
		return ;
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
	init_frames(app);
}
