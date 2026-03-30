/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:37:29 by stefan           #+#    #+#             */
/*   Updated: 2025/08/24 22:37:29 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_parse_error	check_all_elements_found(t_parse_file_data *file_data, t_app *app)
{
	file_data->all_found = true;
	file_data->i = 0;
	while (file_data->i < ELEMENT_COUNT)
	{
		if (!app->map->elements_found[file_data->i])
		{
			file_data->all_found = false;
			break ;
		}
		file_data->i++;
	}
	if (file_data->all_found)
		file_data->elements_fully_parsed = true;
	return (PARSE_SUCCESS);
}

t_parse_error	process_element_line(t_parse_file_data *file_data, t_app *app)
{
	t_parse_error	error;

	error = parse_element(file_data->trimmed_line, app);
	if (error == PARSE_SUCCESS)
		return (check_all_elements_found(file_data, app));
	free(file_data->line);
	close(file_data->fd);
	return (error);
}
