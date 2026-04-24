/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:23:36 by sruff             #+#    #+#             */
/*   Updated: 2026/03/30 12:49:09 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_wall_texture(mlx_texture_t	**wall_texture, const char *path)
{
	(*wall_texture) = mlx_load_png(path);
	if (!(*wall_texture))
		return (0);
	return (1);
}

int	load_wall_textures(t_app *app)
{
	load_wall_texture(&(app->img->txt_no), app->map->north_texture_path);
	load_wall_texture(&(app->img->txt_so), app->map->south_texture_path);
	load_wall_texture(&(app->img->txt_ea), app->map->east_texture_path);
	load_wall_texture(&(app->img->txt_we), app->map->west_texture_path);
	if (!app->img->txt_no
		|| !app->img->txt_so
		|| !app->img->txt_ea
		|| !app->img->txt_we)
	{
		cleanup_textures(app->img);
		return (0);
	}
	return (1);
}
