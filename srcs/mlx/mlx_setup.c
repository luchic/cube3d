/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:05:25 by sruff             #+#    #+#             */
/*   Updated: 2025/08/24 18:57:58 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_img(t_app *app)
{
	app->img->screen = mlx_new_image(app->mlx, app->window_width,
			app->window_height);
	if (!app->img->screen || !app->img->screen->pixels)
		exit_with_error("Failed to alloc screen image", app);
	mlx_image_to_window(app->mlx, app->img->screen, 0, 0);
}
// window size changes apply to app

static void	resize_callback(int32_t width, int32_t height, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (!app || !app->img)
		return ;
	app->window_width = width;
	app->window_height = height;
	if (app->img->screen)
		mlx_delete_image(app->mlx, app->img->screen);
	app->img->screen = mlx_new_image(app->mlx, width, height);
	if (!app->img->screen || !app->img->screen->pixels)
		exit_with_error("Failed to recreate screen image after resize", app);
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
}

void	cleanup_mlx(t_app *app)
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

void	mlx_setup(t_app *app)
{
	app->mlx = mlx_init(app->window_width, app->window_height, "Cub3D", true);
	if (!app->mlx)
	{
		exit_with_error("MLX initialization failed.", app);
	}
	load_all_textures(app);
	init_img(app);
	mlx_resize_hook(app->mlx, resize_callback, app);
}
