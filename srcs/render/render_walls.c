/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:35:37 by stefan           #+#    #+#             */
/*   Updated: 2025/08/14 16:35:37 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_walls(t_app *app)
{
	int32_t			x;
	t_casting_info	info;

	x = 0;
	clean_wall_frame(app->frames.walls_frame);
	while (x < app->window_width)
	{
		info = start_casting(app, x);
		if (info.hit)
		{
			draw_wertical_line(app, info, x);
		}
		x++;
	}
}
