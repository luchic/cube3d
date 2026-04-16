/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:15:36 by sruff             #+#    #+#             */
/*   Updated: 2026/04/16 17:48:49 by sruff            ###   ########.fr       */
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
	t_parse_error error;

	if (argc != 2)
	{
		printf("Usage: %s <path to map_file>\n", argv[0]);
		return (1);
	}
	//app = setup_app(argv[1]);
	app = NULL;
	error = parse_map(app,argv[1]);
	ft_printf("Parsing result: %d \n", error);
	setup_app();
	//app->last_time = mlx_get_time();
	printf("Welcome to Cub3D!\n");
	//mlx_loop(app->mlx);
	//cleanup_graphics(app);
	//ft_clean();
	return (0);
}