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

static t_parse_error	process_texture(const t_texture_element_args *a,
		t_parse_error error_code)
{
	t_map	*map;

	map = a->app->map;
	if (map->elements_found[a->texture_type])
		return (error_code);
	if (!validate_texture_file(a->value))
		return (PARSE_ERR_TEXTURE_FILE);
	*(a->texture_path_ptr) = malloc_strdup(a->value);
	if (!*(a->texture_path_ptr))
		return (PARSE_ERR_ALLOC);
	map->elements_found[a->texture_type] = true;
	return (PARSE_SUCCESS);
}

t_parse_error	handle_texture_element(const t_texture_element_args *a)
{
	if (strcmp(a->key, "NO") == 0 && a->texture_type == NORTH_TEXTURE)
		return (process_texture(a, PARSE_ERR_DUPLICATE_TEXTURE));
	if (strcmp(a->key, "SO") == 0 && a->texture_type == SOUTH_TEXTURE)
		return (process_texture(a, PARSE_ERR_DUPLICATE_TEXTURE));
	if (strcmp(a->key, "WE") == 0 && a->texture_type == WEST_TEXTURE)
		return (process_texture(a, PARSE_ERR_DUPLICATE_TEXTURE));
	if (strcmp(a->key, "EA") == 0 && a->texture_type == EAST_TEXTURE)
		return (process_texture(a, PARSE_ERR_DUPLICATE_TEXTURE));
	return (PARSE_NO_MATCH);
}

t_parse_error	handle_color_element(const t_color_element_args *a)
{
	t_map			*map;
	t_parse_error	error;

	map = a->app->map;
	if (strcmp(a->key, "F") == 0 && a->color_type == FLOOR_COLOR)
	{
		if (map->elements_found[FLOOR_COLOR])
			return (PARSE_ERR_DUPLICATE_COLOR);
		error = parse_color(a->value, a->color_array, a->app);
		if (error != PARSE_SUCCESS)
			return (error);
		map->elements_found[FLOOR_COLOR] = true;
		return (PARSE_SUCCESS);
	}
	if (strcmp(a->key, "C") == 0 && a->color_type == CEILING_COLOR)
	{
		if (map->elements_found[CEILING_COLOR])
			return (PARSE_ERR_DUPLICATE_COLOR);
		error = parse_color(a->value, a->color_array, a->app);
		if (error != PARSE_SUCCESS)
			return (error);
		map->elements_found[CEILING_COLOR] = true;
		return (PARSE_SUCCESS);
	}
	return (PARSE_NO_MATCH);
}
