/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_handler_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:40:31 by stefan           #+#    #+#             */
/*   Updated: 2025/08/24 22:40:31 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture_element_args	get_texture_args(int32_t i, char *line,
		char *value, t_app *app)
{
	t_map	*map;

	map = app->map;
	if (i == 0)
		return ((t_texture_element_args){line, value, app, NORTH_TEXTURE,
			&map->north_texture_path});
	if (i == 1)
		return ((t_texture_element_args){line, value, app, SOUTH_TEXTURE,
			&map->south_texture_path});
	if (i == 2)
		return ((t_texture_element_args){line, value, app, WEST_TEXTURE,
			&map->west_texture_path});
	return ((t_texture_element_args){line, value, app, EAST_TEXTURE,
		&map->east_texture_path});
}

t_parse_error	handle_texture_elements(char *line, char *value, t_app *app)
{
	t_texture_element_args	ta;
	int						i;
	t_parse_error			error;

	i = 0;
	while (i < 4)
	{
		ta = get_texture_args(i, line, value, app);
		error = handle_texture_element(&ta);
		if (error != PARSE_NO_MATCH)
			return (error);
		i++;
	}
	return (PARSE_NO_MATCH);
}
