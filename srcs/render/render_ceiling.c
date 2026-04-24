/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceiling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:25:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/13 15:44:39 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int32_t	interpolate_channel(int32_t start, int32_t end, double factor)
{
	return ((int32_t)(start + (end - start) * factor));
}

static int32_t	get_gradient_color(int32_t base_color, double factor)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;

	r = (base_color >> 24) & 0xFF;
	g = (base_color >> 16) & 0xFF;
	b = (base_color >> 8) & 0xFF;
	r = interpolate_channel(r / 3, r, factor);
	g = interpolate_channel(g / 3, g, factor);
	b = interpolate_channel(b / 3, b, factor);
	return (get_rgba(r, g, b, 255));
}

void	draw_sky(t_app *app, int32_t ceiling_color)
{
	int32_t	x;
	int32_t	y;
	double	factor;
	int32_t	shaded_color;

	y = 0;
	while (y < app->window_height / 2)
	{
		factor = (double)y / (app->window_height / 2);
		shaded_color = get_gradient_color(ceiling_color, factor);
		x = 0;
		while (x < app->window_width)
		{
			mlx_put_pixel(app->img->screen, x, y, shaded_color);
			x++;
		}
		y++;
	}
}
