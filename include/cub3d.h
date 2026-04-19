/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:23:57 by sruff             #+#    #+#             */
/*   Updated: 2026/04/17 16:32:24 by sruff            ###   ########.fr       */
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
# include <string.h>

# define ELEM_NO 0x01
# define ELEM_SO 0x02
# define ELEM_WE 0x04
# define ELEM_EA 0x08
# define ELEM_F  0x10
# define ELEM_C  0x20
# define ELEM_ALL 0x3F

typedef struct s_map
{
	char			**grid;
	int32_t			grid_width;
	int32_t			grid_height;
	char			*north_texture_path;
	char			*south_texture_path;
	char			*west_texture_path;
	char			*east_texture_path;
	int32_t			floor_color[3];
	int32_t			ceiling_color[3];
	int32_t			player_start_x;
	int32_t			player_start_y;
	int8_t			player_start_dir;
}					t_map;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_app
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_map			*map;
	t_player		player;
	int32_t			window_width;
	int32_t			window_height;
}					t_app;

typedef struct s_parse_ctx
{
	int32_t		fd;
	t_map		*map;
	uint8_t		elements_found;
}				t_parse_ctx;

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
t_parse_error	parse_map(t_app *app, const char *file);
t_parse_error	parse_element(char *line, t_parse_ctx *ctx);
t_parse_error	parse_grid(t_parse_ctx *ctx, char *first_line);
t_parse_error	validate_map(t_map *map);
t_parse_error	pad_grid(t_map *map);

//parsing error
void			print_parse_error(t_parse_error error);
const char		*get_parse_error_message(t_parse_error error);

// utils
void			exit_with_error(const char *message, t_app *app);
char			*malloc_strdup(const char *src);
char			**str_array_dup(char **src, int32_t height);
int32_t			validate_texture_file(const char *path);
char			*ft_strpbrk(const char *s, const char *charset);
int				is_empty_line(char *line);
int				check_extension(const char *file, const char *ext);

#endif