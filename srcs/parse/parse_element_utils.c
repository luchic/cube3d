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

bool	check_all_elements_found(t_parse_file_data *file_data, t_app *app)
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
	return (true);
}

bool	process_element_line(t_parse_file_data *file_data, t_app *app)
{
	if (parse_element(file_data->trimmed_line, app))
		return (check_all_elements_found(file_data, app));
	else
	{
		free(file_data->line);
		close(file_data->fd);
		exit_with_error("Invalid line or missing elements before map grid.",
			app);
		return (false);
	}
}
