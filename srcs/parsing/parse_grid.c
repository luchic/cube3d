/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:10:00 by sruff             #+#    #+#             */
/*   Updated: 2026/04/17 12:10:00 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_list	*read_grid_to_list(int fd, char *first_line)
{
	t_list	*list;
	char	*line;

	list = ft_lstnew(malloc_strdup(first_line));
	if (!list)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		ft_lstadd_back(&list, ft_lstnew(malloc_strdup(line)));
		free(line);
	}
	return (list);
}

static char	**convert_list_to_array(t_list *list, int32_t *height, int32_t *width)
{
	char	**grid;
	int32_t	h;
	int32_t	w;
	t_list	*tmp;

	h = ft_lstsize(list);
	grid = ft_calloc(h + 1, sizeof(char *));
	if (!grid)
		return (NULL);
	w = 0;
	tmp = list;
	h = 0;
	while (tmp)
	{
		grid[h] = (char *)tmp->content;
		if ((int32_t)ft_strlen(grid[h]) > w)
			w = ft_strlen(grid[h]);
		tmp = tmp->next;
		h++;
	}
	*height = h;
	*width = w;
	return (grid);
}

t_parse_error	parse_grid(t_parse_ctx *ctx, char *first_line)
{
	t_list	*list;

	list = read_grid_to_list(ctx->fd, first_line);
	if (!list)
		return (PARSE_ERR_ALLOC);
	ctx->map->grid = convert_list_to_array(list, &ctx->map->grid_height, &ctx->map->grid_width);
	// We don't free the content because we moved pointers to the array
	// But we should free the list nodes. 
	// However, simple ft_lstclear would free content if we pass free.
	// We need a clear that doesn't free content.
	t_list *tmp;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
	if (!ctx->map->grid)
		return (PARSE_ERR_ALLOC);
	return (PARSE_SUCCESS);
}
