/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:15:30 by sruff             #+#    #+#             */
/*   Updated: 2026/04/25 15:15:31 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_wall_frame(mlx_image_t *image)
{
	int			color;
	uint32_t	i;
	uint32_t	j;

	color = get_rgba(0, 0, 0, 0);
	i = 0;
	while (i < image->height)
	{
		j = 0;
		while (j < image->width)
		{
			mlx_put_pixel(image, j, i, color);
			j++;
		}
		i++;
	}
}
