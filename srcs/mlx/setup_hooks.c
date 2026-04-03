/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:20:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/03 13:20:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	main_loop_hook(void *param)
{
	t_app	*app;

	app = param;
	movehook(app);
	render(app);
}

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

void	setup_hooks(t_app *app)
{
	mlx_resize_hook(app->mlx, resize_callback, app);
	mlx_loop_hook(app->mlx, main_loop_hook, app);
}
