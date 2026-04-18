/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:35:16 by stefan           #+#    #+#             */
/*   Updated: 2025/08/14 16:35:16 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_pixel(mlx_texture_t *texture, int32_t x, int32_t y)
{
	int32_t	pos;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	pos = (y * texture->width + x) * 4;
	r = texture->pixels[pos];
	g = texture->pixels[pos + 1];
	b = texture->pixels[pos + 2];
	a = texture->pixels[pos + 3];
	return (get_rgba(r, g, b, a));
}
