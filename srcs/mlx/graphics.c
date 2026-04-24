/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:20:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/03 13:20:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_screen_image(t_app *app)
{
	app->img->screen = mlx_new_image(app->mlx, app->window_width,
			app->window_height);
	if (!app->img->screen || !app->img->screen->pixels)
		exit_with_error("Failed to alloc screen image", app);
	mlx_image_to_window(app->mlx, app->img->screen, 0, 0);
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
	if (app->img && app->img->screen)
		mlx_delete_image(app->mlx, app->img->screen);
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
	create_screen_image(app);
}
