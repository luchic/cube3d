/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:58:56 by sruff             #+#    #+#             */
/*   Updated: 2026/04/17 16:33:48 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_parse_error	parse_lines(t_parse_ctx *ctx)
{
	char			*line;
	t_parse_error	error;

	while (1)
	{
		line = get_next_line(ctx->fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		error = parse_element(line, ctx);
		if (error == PARSE_NO_MATCH)
		{
			error = parse_grid(ctx, line);
			free(line);
			return (error);
		}
		free(line);
		if (error != PARSE_SUCCESS)
			return (error);
	}
	if (ctx->elements_found != ELEM_ALL)
		return (PARSE_ERR_MISSING_ELEMENTS);
	return (PARSE_ERR_MAP_GRID_NOT_FOUND);
}

t_parse_error	parse_map(t_app *app, const char *file)
{
	t_parse_ctx		ctx;
	t_parse_error	error;

	if (!check_extension(file, ".cub"))
		return (PARSE_ERR_INVALID_EXTENSION);
	ctx.fd = open(file, O_RDONLY);
	if (ctx.fd < 0)
		return (PARSE_ERR_OPEN_FILE);
	ctx.map = app->map;
	ctx.elements_found = 0;
	error = parse_lines(&ctx);
	close(ctx.fd);
	if (error != PARSE_SUCCESS)
		return (error);
	error = pad_grid(app->map);
	if (error != PARSE_SUCCESS)
		return (error);
	error = validate_map(app->map);
	return (error);
}