/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:39:40 by stefan           #+#    #+#             */
/*   Updated: 2025/08/14 16:39:40 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_parse_error	handle_map_line(char *line, t_app *app,
		t_map_lines_data *data)
{
	char	**new_temp_map_lines;
	char	*duplicated_line;

	if (*(data->temp_map_height) >= *(data->temp_map_capacity))
	{
		*(data->temp_map_capacity) *= 2;
		new_temp_map_lines = ft_malloc(sizeof(char *)
				* (*(data->temp_map_capacity)));
		if (!new_temp_map_lines)
			return (PARSE_ERR_ALLOC);
		ft_memcpy(new_temp_map_lines, *(data->temp_map_lines), sizeof(char *)
			* (*(data->temp_map_height)));
		*(data->temp_map_lines) = new_temp_map_lines;
	}
	duplicated_line = malloc_strdup(line);
	if (!duplicated_line)
		return (PARSE_ERR_ALLOC);
	(*(data->temp_map_lines))[(*(data->temp_map_height))++] = duplicated_line;
	(void)app;
	return (PARSE_SUCCESS);
}

t_parse_error	process_map_line(t_parse_file_data *file_data, t_app *app,
		t_map_lines_data *map_data)
{
	return (handle_map_line(file_data->line, app, map_data));
}

t_parse_error	handle_empty_line(t_parse_file_data *file_data, t_app *app,
		int32_t *consecutive_empty_lines, t_map_lines_data *map_data)
{
	if (file_data->elements_fully_parsed && *(map_data->temp_map_height) > 0)
	{
		(*consecutive_empty_lines)++;
		if (*consecutive_empty_lines >= 1)
		{
			free(file_data->line);
			close(file_data->fd);
			(void)app;
			return (PARSE_ERR_EMPTY_LINE_IN_MAP);
		}
	}
	free(file_data->line);
	return (PARSE_SUCCESS);
}

t_parse_error	process_valid_line(t_parse_file_data *file_data, t_app *app,
		t_map_lines_data *map_data)
{
	t_parse_error	error;

	if (!file_data->elements_fully_parsed)
	{
		error = process_element_line(file_data, app);
		if (error != PARSE_SUCCESS)
			return (error);
	}
	else
	{
		error = process_map_line(file_data, app, map_data);
		if (error != PARSE_SUCCESS)
			return (error);
	}
	free(file_data->line);
	return (PARSE_SUCCESS);
}

t_parse_error	process_file_lines(t_parse_file_data *file_data, t_app *app,
		t_map_lines_data *map_data)
{
	int32_t	consecutive_empty_lines;
	t_parse_error	error;

	consecutive_empty_lines = 0;
	file_data->line = get_next_line(file_data->fd);
	while (file_data->line)
	{
		file_data->trimmed_line = file_data->line;
		while (*file_data->trimmed_line && (*file_data->trimmed_line == ' '
				|| *file_data->trimmed_line == '\t'))
			file_data->trimmed_line++;
		file_data->newline = ft_strchr(file_data->trimmed_line, '\n');
		if (file_data->newline)
			*file_data->newline = '\0';
		if (*file_data->trimmed_line == '\0'
			|| file_data->trimmed_line[0] == '\n')
		{
			error = handle_empty_line(file_data, app, &consecutive_empty_lines,
					map_data);
			if (error != PARSE_SUCCESS)
				return (error);
			file_data->line = get_next_line(file_data->fd);
			continue ;
		}
		consecutive_empty_lines = 0;
		error = process_valid_line(file_data, app, map_data);
		if (error != PARSE_SUCCESS)
			return (error);
		file_data->line = get_next_line(file_data->fd);
	}
	return (PARSE_SUCCESS);
}
