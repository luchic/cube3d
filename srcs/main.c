/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:14:56 by sruff             #+#    #+#             */
/*   Updated: 2026/04/05 11:50:36 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_app	*allocate_app(void)
{
	t_app	*app;

	app = ft_calloc(1, sizeof(t_app));
	if (!app)
		exit_with_error("Memory allocation for app failed.", NULL);
	app->map = ft_calloc(1, sizeof(t_map));
	if (!app->map)
		exit_with_error("Memory allocation for map failed.", app);
	app->img = ft_calloc(1, sizeof(t_images));
	if (!app->img)
		exit_with_error("Memory allocation for images failed.", app);
	return (app);
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
	setup_graphics(app);
	setup_hooks(app);
	return (app);
}

int32_t	main(int32_t argc, char **argv)
{
	t_app	*app;

	if (argc != 2)
	{
		ft_printf("Usage: %s <path to map_file>\n", argv[0]);
		return (1);
	}
	app = setup_app(argv[1]);
	ft_printf("Welcome to Cub3D!\n");
	mlx_loop(app->mlx);
	cleanup_graphics(app);
	ft_clean();
	return (0);
}
// system("leaks cub3d");
