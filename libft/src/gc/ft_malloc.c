/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:43:13 by nluchini          #+#    #+#             */
/*   Updated: 2025/10/16 14:18:06 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*__ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;
	t_list	*new_node;
	t_list	**memory;

	if (size == 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	memory = get_memory();
	new_node = __ft_lstnew(ptr);
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_front(memory, new_node);
	return (ptr);
}
