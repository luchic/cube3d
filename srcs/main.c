/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:28:12 by sruff             #+#    #+#             */
/*   Updated: 2026/04/24 15:28:13 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_app	*allocate_app(void)
{
	t_app	*app;

	app = ft_calloc(1, sizeof(t_app));
	if (!app)
		exit_with_error("Memory allocation for app failed.", NULL);
	app->map = ft_calloc(1, sizeof(t_map));
	if (!app->map)
		exit_with_error("Memory allocation for map failed.", app);
	return (app);
}

static t_app	*setup_app(void)
{
	t_app	*app;

	app = allocate_app();
	// setup_graphics
	// setup_hooks
	return (app);
}

static void	setup_hooks(t_app *app)
{
	mlx_loop_hook(app->mlx, main_loop_hook, app);
}

static t_app	*setup_app(const char *map_path)
{
	t_app			*app;
	t_parse_error	error;

	app = allocate_app();
	error = parse_map(app, map_path);
	if (error != PARSE_SUCCESS)
	{
		print_parse_error(error);
		clean_exit(app);
	}
	app->window_width = WINDOW_WIDTH;
	app->window_height = WINDOW_HEIGHT;
	setup_graphics(app);
	setup_hooks(app);
	return (app);
}

int32_t	main(int32_t argc, char **argv)
{
	t_app			*app;
	t_parse_error	error;

	if (argc != 2)
	{
		printf("Usage: %s <path to map_file>\n", argv[0]);
		return (1);
	}
	ft_printf("Welcome to Cub3D!\n");
	app = setup_app(argv[1]);
	mlx_loop(app->mlx);
	cleanup_graphics(app);
	return (0);
}
