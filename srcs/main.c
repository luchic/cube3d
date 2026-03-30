/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:14:56 by sruff             #+#    #+#             */
/*   Updated: 2026/03/30 10:59:44 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	allocate_app(t_app **app)
{
	*app = ft_calloc(1, sizeof(t_app));
	if (!*app)
		exit_with_error("Memory allocation for app failed.", NULL);
	(*app)->map = ft_calloc(1, sizeof(t_map));
	if (!(*app)->map)
		exit_with_error("Memory allocation for map failed.", *app);
	(*app)->img = ft_calloc(1, sizeof(t_images));
	if (!(*app)->img)
		exit_with_error("Memory allocation for images failed.", *app);
}

static void	main_loop_hook(void *param)
{
	t_app	*app;

	app = param;
	movehook(app);
	render(app);
}

int32_t	main(int32_t argc, char **argv)
{
	t_app	*app;

	if (argc != 2)
	{
		ft_printf("Usage: %s <path to map_file>\n", argv[0]);
		return (1);
	}
	allocate_app(&app);
	ft_printf("Welcome to Cub3D!\n");
	if (parse_map(app, argv[1]) != 0)
	{
		ft_printf("Error: Failed to parse map file\n");
		return (1);
	}
	app->window_width = WINDOW_WIDTH;
	app->window_height = WINDOW_HEIGHT;
	setup_graphics(app);
	mlx_loop_hook(app->mlx, main_loop_hook, app);
	mlx_loop(app->mlx);
	cleanup_graphics(app);
	ft_clean();
	return (0);
}
// system("leaks cub3d");
