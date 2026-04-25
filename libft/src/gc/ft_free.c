/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:43:25 by nluchini          #+#    #+#             */
/*   Updated: 2025/10/16 14:18:11 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free(void *ptr)
{
	t_list	**memory;
	t_list	*current;
	t_list	*prev;

	if (!ptr)
		return ;
	memory = get_memory();
	current = *memory;
	prev = NULL;
	while (current)
	{
		if (current->content == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*memory = current->next;
			free(current->content);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
