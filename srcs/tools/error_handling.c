/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:40:10 by sruff             #+#    #+#             */
/*   Updated: 2026/04/25 12:08:16 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_exit(t_app *app)
{
	cleanup_graphics(app);
	ft_clean();
	exit(1);
}

void	exit_with_error(const char *message, t_app *app)
{
	ft_printf("Error: %s\n", message);
	if (app)
	{
		cleanup_graphics(app);
		if (app->mlx)
			mlx_terminate(app->mlx);
	}
	ft_clean();
	exit(1);
}
