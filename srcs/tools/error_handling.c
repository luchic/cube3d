/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:20:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/03 13:20:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_exit(t_app *app)
{
	cleanup_graphics(app);
	ft_clean();
	exit(1);
}

void	print_parse_error(t_parse_error error)
{
	ft_printf("Error: %s\n", get_parse_error_message(error));
}

void	exit_with_error(const char *message, t_app *app)
{
	ft_printf("Error: %s\n", message);
	if (app)
	{
		if (app->image)
			mlx_delete_image(app->mlx, app->image);
		if (app->mlx)
			mlx_terminate(app->mlx);
	}
	ft_clean();
	exit(1);
}

static const char	*get_rest_error_messages(t_parse_error error)
{
	if (error == PARSE_ERR_DUPLICATE_TEXTURE)
		return ("Duplicate texture definition.");
	if (error == PARSE_ERR_TEXTURE_FILE)
		return ("Texture file not found or inaccessible.");
	if (error == PARSE_ERR_DUPLICATE_COLOR)
		return ("Duplicate color definition.");
	if (error == PARSE_ERR_INVALID_RGB)
		return ("Invalid RGB color format.");
	if (error == PARSE_ERR_INVALID_MAP_CHAR)
		return ("Invalid character in map grid.");
	if (error == PARSE_ERR_INVALID_PLAYER_COUNT)
		return ("Map must have exactly one player start position.");
	if (error == PARSE_ERR_MAP_NOT_ENCLOSED)
		return ("Map is not enclosed by walls.");
	return ("Unknown parse error.");
}

const char	*get_parse_error_message(t_parse_error error)
{
	if (error == PARSE_ERR_INVALID_EXTENSION)
		return ("Map file must have a .cub extension.");
	if (error == PARSE_ERR_OPEN_FILE)
		return ("Could not open map file.");
	if (error == PARSE_ERR_ALLOC)
		return ("Memory allocation failed during parsing.");
	if (error == PARSE_ERR_MISSING_ELEMENTS)
		return ("Missing one or more map elements.");
	if (error == PARSE_ERR_MAP_GRID_NOT_FOUND)
		return ("Map grid not found in file.");
	if (error == PARSE_ERR_EMPTY_LINE_IN_MAP)
		return ("Empty line found in map section.");
	if (error == PARSE_ERR_INVALID_LINE || error == PARSE_NO_MATCH)
		return ("Invalid line or missing elements before map grid.");
	return (get_rest_error_messages(error));
}
