/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:40:05 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/27 13:47:01 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putlnbr_fd(long n, int fd)
{
	int				res;
	unsigned long	nbr;
	char			*base;

	nbr = n;
	base = "0123456789";
	if (n < 0)
	{
		nbr = ((unsigned long)-(n + 1) + 1);
		if (ft_putchar_fd('-', fd) == -1)
			return (-1);
		res = ft_putulnbr_base_fd(nbr, base, fd);
		if (res == -1)
			return (-1);
		return (res + 1);
	}
	return (ft_putulnbr_base_fd(nbr, base, fd));
}
