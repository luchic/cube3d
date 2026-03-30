/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:39:18 by stefan           #+#    #+#             */
/*   Updated: 2025/08/24 22:39:18 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO: To refactore; read_and_parse. Maybe devide responsobilities.
t_parse_error	read_and_parse_file(const char *filename, t_app *app)
{
	t_parse_file_data	file_data;
	t_map_lines_data	map_data;
	char				**temp_map_lines;
	int32_t				temp_map_height;
	int32_t				temp_map_capacity;
	t_parse_error		error;

	temp_map_height = 0;
	temp_map_capacity = 10;
	temp_map_lines = ft_malloc(sizeof(char *) * temp_map_capacity);
	if (!temp_map_lines)
		return (PARSE_ERR_ALLOC);
	map_data = (t_map_lines_data){&temp_map_lines, &temp_map_height,
		&temp_map_capacity};
	file_data = (t_parse_file_data){0};
	file_data.fd = open(filename, O_RDONLY);
	if (file_data.fd < 0)
		return (PARSE_ERR_OPEN_FILE);
	error = process_file_lines(&file_data, app, &map_data);
	if (error != PARSE_SUCCESS)
	{
		close(file_data.fd);
		return (error);
	}
	close(file_data.fd);
	if (!file_data.elements_fully_parsed)
		return (PARSE_ERR_MISSING_ELEMENTS);
	if (temp_map_height == 0)
		return (PARSE_ERR_MAP_GRID_NOT_FOUND);
	app->map->grid = temp_map_lines;
	app->map->grid_height = temp_map_height;
	return (PARSE_SUCCESS);
}
