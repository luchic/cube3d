/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:23:36 by sruff             #+#    #+#             */
/*   Updated: 2026/04/25 12:17:43 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static int	load_texture(mlx_texture_t **texture, const char *path)
{
	(*texture) = mlx_load_png(path);
	if (!(*texture))
		return (0);
	return (1);
}

void	cleanup_textures(t_images *textures)
{
	if (!textures)
		return ;
	if (textures->txt_ea)
		mlx_delete_texture(textures->txt_ea);
	if (textures->txt_no)
		mlx_delete_texture(textures->txt_no);
	if (textures->txt_so)
		mlx_delete_texture(textures->txt_so);
	if (textures->txt_we)
		mlx_delete_texture(textures->txt_we);
}

int	load_textures(t_app *app)
{
	load_texture(&(app->img->txt_no), app->map->north_texture_path);
	load_texture(&(app->img->txt_so), app->map->south_texture_path);
	load_texture(&(app->img->txt_ea), app->map->east_texture_path);
	load_texture(&(app->img->txt_we), app->map->west_texture_path);
	if (!app->img->txt_no || !app->img->txt_so || !app->img->txt_ea
		|| !app->img->txt_we)
	{
		cleanup_textures(app->img);
		return (0);
	}
	return (1);
}
