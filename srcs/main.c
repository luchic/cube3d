/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:15:36 by sruff             #+#    #+#             */
/*   Updated: 2026/04/24 15:17:46 by sruff            ###   ########.fr       */
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

static t_app	*setup_app()
{
	t_app			*app;

	app = allocate_app();
	//setup_graphics
	//setup_hooks
	return (app);
}

int32_t	main(int32_t argc, char **argv)
{
	t_app	*app;
	t_parse_error	error;

	if (argc != 2)
	{
		printf("Usage: %s <path to map_file>\n", argv[0]);
		return (1);
	}
	app = setup_app();
	error = parse_map(app, argv[1]);
	if (error){
		print_parse_error(error);
		ft_clean();
		return 1;
	}
	//app->last_time = mlx_get_time();
	//debug_print_map(app->map);
	//ft_printf("Welcome to Cub3D!\n");
	//mlx_loop(app->mlx);
	//cleanup_graphics(app);
	ft_clean();
	return (0);
}
