/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:37:45 by stefan           #+#    #+#             */
/*   Updated: 2025/08/24 20:32:00 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h> // strcmp

static bool	process_texture(const t_texture_element_args *a, const char *msg)
{
	t_map	*map;

	map = a->app->map;
	if (map->elements_found[a->texture_type])
		exit_with_error((char *)msg, a->app);
	if (!validate_texture_file(a->value))
		exit_with_error("Texture file not found or inaccessible.", a->app);
	*(a->texture_path_ptr) = malloc_strdup(a->value);
	map->elements_found[a->texture_type] = true;
	return (true);
}

bool	handle_texture_element(const t_texture_element_args *a)
{
	if (strcmp(a->key, "NO") == 0 && a->texture_type == NORTH_TEXTURE)
		return (process_texture(a, "Duplicate NO texture."));
	if (strcmp(a->key, "SO") == 0 && a->texture_type == SOUTH_TEXTURE)
		return (process_texture(a, "Duplicate SO texture."));
	if (strcmp(a->key, "WE") == 0 && a->texture_type == WEST_TEXTURE)
		return (process_texture(a, "Duplicate WE texture."));
	if (strcmp(a->key, "EA") == 0 && a->texture_type == EAST_TEXTURE)
		return (process_texture(a, "Duplicate EA texture."));
	return (false);
}

bool	handle_color_element(const t_color_element_args *a)
{
	t_map	*map;

	map = a->app->map;
	if (strcmp(a->key, "F") == 0 && a->color_type == FLOOR_COLOR)
	{
		if (map->elements_found[FLOOR_COLOR])
			exit_with_error("Duplicate F color.", a->app);
		parse_color(a->value, a->color_array, a->app);
		map->elements_found[FLOOR_COLOR] = true;
		return (true);
	}
	if (strcmp(a->key, "C") == 0 && a->color_type == CEILING_COLOR)
	{
		if (map->elements_found[CEILING_COLOR])
			exit_with_error("Duplicate C color.", a->app);
		parse_color(a->value, a->color_array, a->app);
		map->elements_found[CEILING_COLOR] = true;
		return (true);
	}
	return (false);
}
