/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_map_grid_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:15:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/03 13:15:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_parse_error	pad_map_line(t_map *map, int32_t i)
{
	int32_t	len;
	int32_t	j;
	char	*new_line;

	len = ft_strlen(map->grid[i]);
	if (len >= map->grid_width)
		return (PARSE_SUCCESS);
	new_line = ft_malloc(map->grid_width + 1);
	if (!new_line)
		return (PARSE_ERR_ALLOC);
	ft_memcpy(new_line, map->grid[i], len);
	j = len;
	while (j < map->grid_width)
		new_line[j++] = ' ';
	new_line[map->grid_width] = '\0';
	map->grid[i] = new_line;
	return (PARSE_SUCCESS);
}
