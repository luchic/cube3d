/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:00:00 by sruff             #+#    #+#             */
/*   Updated: 2026/04/19 18:31:11 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_parse_error	parse_texture(char **split, char **path, uint8_t bit,
		t_parse_ctx *ctx)
{
	if (ctx->elements_found & bit)
		return (PARSE_ERR_DUPLICATE_TEXTURE);
	if (!split[1] || split[2])
		return (PARSE_ERR_INVALID_LINE);
	*path = malloc_strdup(split[1]);
	if (!*path)
		return (PARSE_ERR_ALLOC);
	ctx->elements_found |= bit;
	return (PARSE_SUCCESS);
}

static int	is_digit_str(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static t_parse_error	parse_color(char **split, int32_t color[3], uint8_t bit,
		t_parse_ctx *ctx)
{
	char	**rgb;
	int		i;
	int		val;

	if (ctx->elements_found & bit)
		return (PARSE_ERR_DUPLICATE_COLOR);
	if (!split[1] || split[2])
		return (PARSE_ERR_INVALID_LINE);
	rgb = ft_split(split[1], ',');
	if (!rgb)
		return (PARSE_ERR_ALLOC);
	i = -1;
	while (rgb[++i])
	{
		val = ft_atoi(rgb[i]);
		if (i >= 3 || !is_digit_str(rgb[i]) || val < 0 || val > 255)
			return (PARSE_ERR_INVALID_RGB);
		color[i] = val;
	}
	if (i != 3)
		return (PARSE_ERR_INVALID_RGB);
	ctx->elements_found |= bit;
	return (PARSE_SUCCESS);
}

t_parse_error	parse_element(char *line, t_parse_ctx *ctx)
{
	char 			**split;
	t_parse_error	err;

	if (!line || !*line)
		return (PARSE_NO_MATCH);
	split = ft_split(line, ' ');
	if (!split)
		return (PARSE_ERR_ALLOC);
	if (!split[0])
		return (PARSE_NO_MATCH);
	err = PARSE_NO_MATCH;
	if (!ft_strcmp(split[0], "NO"))
		err = parse_texture(split, &ctx->map->north_texture_path, ELEM_NO, ctx);
	else if (!ft_strcmp(split[0], "SO"))
		err = parse_texture(split, &ctx->map->south_texture_path, ELEM_SO, ctx);
	else if (!ft_strcmp(split[0], "WE"))
		err = parse_texture(split, &ctx->map->west_texture_path, ELEM_WE, ctx);
	else if (!ft_strcmp(split[0], "EA"))
		err = parse_texture(split, &ctx->map->east_texture_path, ELEM_EA, ctx);
	else if (!ft_strcmp(split[0], "F"))
		err = parse_color(split, ctx->map->floor_color, ELEM_F, ctx);
	else if (!ft_strcmp(split[0], "C"))
		err = parse_color(split, ctx->map->ceiling_color, ELEM_C, ctx);
	return (err);
}
