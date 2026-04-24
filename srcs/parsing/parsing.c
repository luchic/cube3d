/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:58:56 by sruff             #+#    #+#             */
/*   Updated: 2026/04/24 17:21:56 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_parse_error	parse_elements_loop(t_parse_ctx *ctx)
{
	char			*line;
	t_parse_error	err;

	while (ctx->elements_found < ELEM_ALL)
	{
		line = get_next_line(ctx->fd);
		if (!line)
			return (PARSE_ERR_MISSING_ELEMENTS);
		err = parse_element(line, ctx);
		if (err != PARSE_SUCCESS && err != PARSE_NO_MATCH)
			return (err);
	}
	return (PARSE_SUCCESS);
}

static t_parse_error	find_grid_start(t_parse_ctx *ctx, char **first_line)
{
	char	*line;

	while (1)
	{
		line = get_next_line(ctx->fd);
		if (!line)
			return (PARSE_ERR_MAP_GRID_NOT_FOUND);
		if (!is_empty_line(line))
		{
			*first_line = line;
			break ;
		}
	}
	return (PARSE_SUCCESS);
}

t_parse_error	parse_map(t_app *app, const char *file)
{
	t_parse_ctx ctx;
	char *first_line;
	t_parse_error err;

	if (!check_extension(file, ".cub"))
		return (PARSE_ERR_INVALID_EXTENSION);
	ctx.fd = open(file, O_RDONLY);
	if (ctx.fd < 0)
		return (PARSE_ERR_OPEN_FILE);
	ctx.map = app->map;
	ctx.elements_found = 0;
	err = parse_elements_loop(&ctx);
	if (err != PARSE_SUCCESS)
		return (close(ctx.fd), err);
	err = find_grid_start(&ctx, &first_line);
	if (err != PARSE_SUCCESS)
		return (close(ctx.fd), err);
	err = parse_grid(&ctx, first_line);
	close(ctx.fd);
	if (err != PARSE_SUCCESS)
		return (err);
	return (validate_map(ctx.map));
}