/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:15:36 by sruff             #+#    #+#             */
/*   Updated: 2026/04/16 16:21:56 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
int32_t	main(int32_t argc, char **argv)
{
	//t_app	*app;
	t_parse_error error;

	if (argc != 2)
	{
		printf("Usage: %s <path to map_file>\n", argv[0]);
		return (1);
	}
	//app = setup_app(argv[1]);
	error = parse_map(argv[1]);
	ft_printf("Parsing result: %d \n", error);
	//app->last_time = mlx_get_time();
	printf("Welcome to Cub3D!\n");
	//mlx_loop(app->mlx);
	//cleanup_graphics(app);
	//ft_clean();
	return (0);
}