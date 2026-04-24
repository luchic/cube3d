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
	t_parse_error		error;

	error = init_file_read(filename, &file_data, &map_data);
	if (error != PARSE_SUCCESS)
		return (error);
	error = process_file_lines(&file_data, app, &map_data);
	if (error != PARSE_SUCCESS)
	{
		close(file_data.fd);
		return (error);
	}
	return (finalize_parsed_map(&file_data, app, *map_data.temp_map_lines,
			*map_data.temp_map_height));
}
