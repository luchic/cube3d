/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:45:29 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/27 13:47:24 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	counter;
	size_t	src_size;

	src_size = ft_strlen(src);
	if (dstsize == 0)
		return (src_size);
	counter = 0;
	while (counter < dstsize - 1 && src[counter] != '\0')
	{
		dest[counter] = src[counter];
		counter++;
	}
	dest[counter] = '\0';
	return (src_size);
}
