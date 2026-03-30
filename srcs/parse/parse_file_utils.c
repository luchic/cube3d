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

void	read_and_parse_file(const char *filename, t_app *app)
{
	t_parse_file_data	file_data;
	t_map_lines_data	map_data;
	char				**temp_map_lines;
	int32_t				temp_map_height;
	int32_t				temp_map_capacity;

	temp_map_height = 0;
	temp_map_capacity = 10;
	temp_map_lines = ft_malloc(sizeof(char *) * temp_map_capacity);
	if (!temp_map_lines)
		exit_with_error("Memory allocation failed for map lines.", app);
	map_data = (t_map_lines_data){&temp_map_lines, &temp_map_height,
		&temp_map_capacity};
	file_data = (t_parse_file_data){0};
	file_data.fd = open(filename, O_RDONLY);
	if (file_data.fd < 0)
		exit_with_error("Could not open map file.", NULL);
	process_file_lines(&file_data, app, &map_data);
	close(file_data.fd);
	if (!file_data.elements_fully_parsed)
		exit_with_error("Missing one or more map elements in file.", app);
	if (temp_map_height == 0)
		exit_with_error("Map grid not found in file.", app);
	app->map->grid = temp_map_lines;
	app->map->grid_height = temp_map_height;
}
