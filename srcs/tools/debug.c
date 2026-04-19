/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 19:17:30 by sruff             #+#    #+#             */
/*   Updated: 2026/04/19 19:17:38 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	debug_print_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	ft_printf("\n--- MAP DEBUG INFO ---\n");
	ft_printf("North Texture: [%s]\n", map->north_texture_path);
	ft_printf("South Texture: [%s]\n", map->south_texture_path);
	ft_printf("West Texture:  [%s]\n", map->west_texture_path);
	ft_printf("East Texture:  [%s]\n", map->east_texture_path);
	ft_printf("Floor Color:   R:%d, G:%d, B:%d\n", map->floor_color[0],
		map->floor_color[1], map->floor_color[2]);
	ft_printf("Ceiling Color: R:%d, G:%d, B:%d\n", map->ceiling_color[0],
		map->ceiling_color[1], map->ceiling_color[2]);
	ft_printf("Player Start:  X:%d, Y:%d, Dir:%c\n", map->player_start_x,
		map->player_start_y, map->player_start_dir);
	ft_printf("Grid Size:     %dx%d\n", map->grid_width, map->grid_height);
	ft_printf("--- GRID ---\n");
	i = 0;
	while (map->grid && map->grid[i])
	{
		ft_printf("%s\n", map->grid[i]);
		i++;
	}
	ft_printf("----------------------\n\n");
}
