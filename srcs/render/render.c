/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:50:30 by sruff             #+#    #+#             */
/*   Updated: 2026/04/25 12:23:55 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_app *app)
{
	int32_t	ceiling_color;
	int32_t	floor_color;

	ceiling_color = get_rgba(app->map->ceiling_color[0],
			app->map->ceiling_color[1], app->map->ceiling_color[2], 255);
	floor_color = get_rgba(app->map->floor_color[0],
			app->map->floor_color[1], app->map->floor_color[2], 255);
	draw_sky(app, ceiling_color);
	draw_floor(app, floor_color);
}

static void	re_draw(t_app *app)
{
	if (!app || !app->img)
		return ;
	render_walls(app);
	render_minimap(app);
}

void	render(t_app *app)
{
	re_draw(app);
}
