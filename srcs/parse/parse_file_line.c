/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:20:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/03 13:20:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	prepare_current_line(t_parse_file_data *file_data)
{
	file_data->trimmed_line = file_data->line;
	while (*file_data->trimmed_line && (*file_data->trimmed_line == ' '
			|| *file_data->trimmed_line == '\t'))
		file_data->trimmed_line++;
	file_data->newline = ft_strchr(file_data->trimmed_line, '\n');
	if (file_data->newline)
		*file_data->newline = '\0';
}

t_parse_error	handle_file_line(t_parse_file_data *file_data, t_app *app,
		int32_t *consecutive_empty_lines, t_map_lines_data *map_data)
{
	t_parse_error	error;

	prepare_current_line(file_data);
	if (*file_data->trimmed_line == '\0')
		return (handle_empty_line(file_data, app,
				consecutive_empty_lines, map_data));
	*consecutive_empty_lines = 0;
	error = process_valid_line(file_data, app, map_data);
	if (error != PARSE_SUCCESS)
		return (error);
	return (PARSE_SUCCESS);
}
