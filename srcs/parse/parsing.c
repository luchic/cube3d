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

static bool	has_cub_extension(const char *file)
{
	size_t	len;

	if (!file)
		return (false);
	len = ft_strlen(file);
	if (len < 4)
		return (false);
	return (ft_strncmp(file + len - 4, ".cub", 5) == 0);
}

static t_parse_error	element_handler(char *line, char *value, t_app *app)
{
	t_color_element_args	ca;
	t_parse_error			error;

	error = handle_texture_elements(line, value, app);
	if (error != PARSE_NO_MATCH)
		return (error);
	ca = (t_color_element_args){line, value, app, FLOOR_COLOR,
		app->map->floor_color};
	error = handle_color_element(&ca);
	if (error != PARSE_NO_MATCH)
		return (error);
	ca.color_type = CEILING_COLOR;
	ca.color_array = app->map->ceiling_color;
	return (handle_color_element(&ca));
}

t_parse_error	parse_element(char *line, t_app *app)
{
	char	*value;
	char	*newline;

	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	newline = ft_strchr(line, '\n');
	if (newline)
		*newline = '\0';
	if (*line == '\0')
		return (PARSE_SUCCESS);
	value = ft_strpbrk(line, " \t");
	if (!value)
		return (PARSE_ERR_INVALID_LINE);
	*value++ = '\0';
	while (*value && (*value == ' ' || *value == '\t'))
		value++;
	return (element_handler(line, value, app));
}

t_parse_error	parse_map(t_app *app, const char *file)
{
	t_parse_error	error;

	if (!has_cub_extension(file))
		return (PARSE_ERR_INVALID_EXTENSION);
	error = read_and_parse_file(file, app);
	if (error != PARSE_SUCCESS)
		return (error);
	error = pad_map_grid(app);
	if (error != PARSE_SUCCESS)
		return (error);
	error = validate_map(app);
	if (error != PARSE_SUCCESS)
		return (error);
	init_player(app);
	return (PARSE_SUCCESS);
}
