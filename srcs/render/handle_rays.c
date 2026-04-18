/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 18:07:58 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/18 21:11:27 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3d.h"

void	init_floor_row(t_app *app, t_floor_view *view, t_floor_row *floor_row,
		int32_t y)
{
	floor_row->row_distance = (0.5 * app->window_height) / (y
			- app->window_height / 2);
	floor_row->floor_step_x = floor_row->row_distance * (view->ray_dir_x1
			- view->ray_dir_x0) / app->window_width;
	floor_row->floor_step_y = floor_row->row_distance * (view->ray_dir_y1
			- view->ray_dir_y0) / app->window_width;
	floor_row->floor_x = app->player.pos_x + floor_row->row_distance
		* view->ray_dir_x0;
	floor_row->floor_y = app->player.pos_y + floor_row->row_distance
		* view->ray_dir_y0;
	floor_row->factor = (double)(y - app->window_height / 2)
		/ (app->window_height / 2);
}
