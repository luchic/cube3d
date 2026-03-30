/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:23:36 by sruff             #+#    #+#             */
/*   Updated: 2025/08/24 19:00:26 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_north_texture(t_app *app)
{
	app->img->txt_no = mlx_load_png(app->map->north_texture_path);
	if (!app->img->txt_no)
	{
		cleanup_textures(app->img);
		exit_with_error("Failed to load north texture.", app);
	}
}

static void	load_south_texture(t_app *app)
{
	app->img->txt_so = mlx_load_png(app->map->south_texture_path);
	if (!app->img->txt_so)
	{
		cleanup_textures(app->img);
		exit_with_error("Failed to load south texture.", app);
	}
}

static void	load_east_texture(t_app *app)
{
	app->img->txt_ea = mlx_load_png(app->map->east_texture_path);
	if (!app->img->txt_ea)
	{
		cleanup_textures(app->img);
		exit_with_error("Failed to load east texture.", app);
	}
}

static void	load_west_texture(t_app *app)
{
	app->img->txt_we = mlx_load_png(app->map->west_texture_path);
	if (!app->img->txt_we)
	{
		cleanup_textures(app->img);
		exit_with_error("Failed to load west texture.", app);
	}
}

void	load_textures(t_app *app)
{
	load_north_texture(app);
	load_south_texture(app);
	load_east_texture(app);
	load_west_texture(app);
}
