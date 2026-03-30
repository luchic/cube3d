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

bool	handle_texture_elements(char *line, char *value, t_app *app)
{
	t_texture_element_args	ta;
	t_map					*map;
	int						i;

	map = app->map;
	i = 0;
	while (i < 4)
	{
		if (i == 0)
			ta = (t_texture_element_args){line, value, app, NORTH_TEXTURE,
				&map->north_texture_path};
		else if (i == 1)
			ta = (t_texture_element_args){line, value, app, SOUTH_TEXTURE,
				&map->south_texture_path};
		else if (i == 2)
			ta = (t_texture_element_args){line, value, app, WEST_TEXTURE,
				&map->west_texture_path};
		else
			ta = (t_texture_element_args){line, value, app, EAST_TEXTURE,
				&map->east_texture_path};
		if (handle_texture_element(&ta))
			return (true);
		i++;
	}
	return (false);
}
