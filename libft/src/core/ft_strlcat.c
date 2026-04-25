/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:55:21 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/27 13:47:20 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	counter;
	size_t	size_dest;
	size_t	size_src;

	size_src = ft_strlen(src);
	if (dstsize == 0)
		return (size_src);
	size_dest = ft_strlen(dest);
	counter = 0;
	while (dest[counter] != '\0')
		counter++;
	while (*src != '\0' && counter < dstsize - 1)
	{
		dest[counter] = *src;
		counter++;
		src++;
	}
	dest[counter] = '\0';
	if (dstsize < size_dest)
		return (size_src + dstsize);
	return (size_dest + size_src);
}
