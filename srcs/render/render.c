/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:50:30 by sruff             #+#    #+#             */
/*   Updated: 2026/04/25 11:08:01 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
