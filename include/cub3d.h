/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:23:57 by sruff             #+#    #+#             */
/*   Updated: 2026/04/16 16:17:33 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef CUB3D_H
#define CUB3D_H

# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/libft.h"
# include "../mlx42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# include <stdio.h>


typedef enum e_parse_error
{
	PARSE_NO_MATCH = -1,
	PARSE_SUCCESS = 0,
	PARSE_ERR_INVALID_EXTENSION,
	PARSE_ERR_OPEN_FILE,
	PARSE_ERR_ALLOC,
	PARSE_ERR_MISSING_ELEMENTS,
	PARSE_ERR_MAP_GRID_NOT_FOUND,
	PARSE_ERR_EMPTY_LINE_IN_MAP,
	PARSE_ERR_INVALID_LINE,
	PARSE_ERR_DUPLICATE_TEXTURE,
	PARSE_ERR_TEXTURE_FILE,
	PARSE_ERR_DUPLICATE_COLOR,
	PARSE_ERR_INVALID_RGB,
	PARSE_ERR_INVALID_MAP_CHAR,
	PARSE_ERR_INVALID_PLAYER_COUNT,
	PARSE_ERR_MAP_NOT_ENCLOSED,
}					t_parse_error;

//parsing
t_parse_error	parse_map(const char *file);

// utils
char			*malloc_strdup(const char *src);
char			**str_array_dup(char **src, int32_t height);
int32_t			validate_texture_file(const char *path);
char			*ft_strpbrk(const char *s, const char *charset);

#endif