/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:20:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/03 13:20:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_parse_error	init_file_read(const char *filename,
		t_parse_file_data *file_data, t_map_lines_data *map_data)
{
	static char		**temp_map_lines;
	static int32_t	temp_map_height;
	static int32_t	temp_map_capacity;

	temp_map_height = 0;
	temp_map_capacity = 10;
	temp_map_lines = ft_malloc(sizeof(char *) * temp_map_capacity);
	if (!temp_map_lines)
		return (PARSE_ERR_ALLOC);
	*map_data = (t_map_lines_data){&temp_map_lines, &temp_map_height,
		&temp_map_capacity};
	*file_data = (t_parse_file_data){0};
	file_data->fd = open(filename, O_RDONLY);
	if (file_data->fd < 0)
		return (PARSE_ERR_OPEN_FILE);
	return (PARSE_SUCCESS);
}

t_parse_error	finalize_parsed_map(t_parse_file_data *file_data, t_app *app,
		char **temp_map_lines, int32_t temp_map_height)
{
	close(file_data->fd);
	if (!file_data->elements_fully_parsed)
		return (PARSE_ERR_MISSING_ELEMENTS);
	if (temp_map_height == 0)
		return (PARSE_ERR_MAP_GRID_NOT_FOUND);
	app->map->grid = temp_map_lines;
	app->map->grid_height = temp_map_height;
	return (PARSE_SUCCESS);
}
