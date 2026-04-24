/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:15:48 by sruff             #+#    #+#             */
/*   Updated: 2025/08/24 22:41:20 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	element_handler(char *line, char *value, t_app *app)
{
	t_color_element_args	ca;

	if (handle_texture_elements(line, value, app))
		return (true);
	ca = (t_color_element_args){line, value, app, FLOOR_COLOR,
		app->map->floor_color};
	if (handle_color_element(&ca))
		return (true);
	ca.color_type = CEILING_COLOR;
	ca.color_array = app->map->ceiling_color;
	return (handle_color_element(&ca));
}

bool	parse_element(char *line, t_app *app)
{
	char	*value;
	char	*newline;

	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	newline = ft_strchr(line, '\n');
	if (newline)
		*newline = '\0';
	if (*line == '\0')
		return (true);
	value = ft_strpbrk(line, " \t");
	if (!value)
		return (false);
	*value++ = '\0';
	while (*value && (*value == ' ' || *value == '\t'))
		value++;
	return (element_handler(line, value, app));
}

int32_t	parse_map(t_app *app, const char *file)
{
	if (!ft_strnstr(file, ".cub", ft_strlen(file)))
		exit_with_error("Map file must have a .cub extension.", NULL);
	read_and_parse_file(file, app);
	pad_map_grid(app);
	validate_map(app);
	init_player(app);
	return (0);
}
