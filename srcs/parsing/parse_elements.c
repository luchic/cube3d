/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:00:00 by sruff             #+#    #+#             */
/*   Updated: 2026/04/17 12:00:00 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	parse_rgb(char *str, int32_t *color)
{
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split)
		return (0);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		// ft_free_split(split);
		return (0);
	}
	color[0] = ft_atoi(split[0]);
	color[1] = ft_atoi(split[1]);
	color[2] = ft_atoi(split[2]);
	// ft_free_split(split);
	if (color[0] < 0 || color[0] > 255 || color[1] < 0 || color[1] > 255
		|| color[2] < 0 || color[2] > 255)
		return (0);
	return (1);
}

static t_parse_error	set_texture(char **path_ptr, char *line, uint8_t *found, uint8_t bit)
{
	if (*found & bit)
		return (PARSE_ERR_DUPLICATE_TEXTURE);
	while (*line && ft_isspace(*line))
		line++;
	*path_ptr = malloc_strdup(line);
	if (!*path_ptr)
		return (PARSE_ERR_ALLOC);
	if (!validate_texture_file(*path_ptr))
		return (PARSE_ERR_TEXTURE_FILE);
	*found |= bit;
	return (PARSE_SUCCESS);
}

static t_parse_error	set_color(int32_t *color_ptr, char *line, uint8_t *found, uint8_t bit)
{
	if (*found & bit)
		return (PARSE_ERR_DUPLICATE_COLOR);
	while (*line && ft_isspace(*line))
		line++;
	if (!parse_rgb(line, color_ptr))
		return (PARSE_ERR_INVALID_RGB);
	*found |= bit;
	return (PARSE_SUCCESS);
}

t_parse_error	parse_element(char *line, t_parse_ctx *ctx)
{
	while (*line && ft_isspace(*line))
		line++;
	if (!*line)
		return (PARSE_SUCCESS);
	if (!ft_strncmp(line, "NO ", 3))
		return (set_texture(&ctx->map->north_texture_path, line + 3, &ctx->elements_found, ELEM_NO));
	if (!ft_strncmp(line, "SO ", 3))
		return (set_texture(&ctx->map->south_texture_path, line + 3, &ctx->elements_found, ELEM_SO));
	if (!ft_strncmp(line, "WE ", 3))
		return (set_texture(&ctx->map->west_texture_path, line + 3, &ctx->elements_found, ELEM_WE));
	if (!ft_strncmp(line, "EA ", 3))
		return (set_texture(&ctx->map->east_texture_path, line + 3, &ctx->elements_found, ELEM_EA));
	if (!ft_strncmp(line, "F ", 2))
		return (set_color(ctx->map->floor_color, line + 2, &ctx->elements_found, ELEM_F));
	if (!ft_strncmp(line, "C ", 2))
		return (set_color(ctx->map->ceiling_color, line + 2, &ctx->elements_found, ELEM_C));
	if (ctx->elements_found == ELEM_ALL)
		return (PARSE_NO_MATCH);
	return (PARSE_ERR_INVALID_LINE);
}
