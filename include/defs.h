
#ifndef DEFS_H
# define DEFS_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define MOVE_SPEED 0.05
# define ROTATE_SPPED 0.06
# define PLAYER_RADIUS 0.25
# define MINIMAP_MARGIN 16
# define MINIMAP_TILE_SIZE 18
# define MINIMAP_VISIBLE_TILES 9
# define MINIMAP_PLAYER_SIZE 6
# define MINIMAP_DIRECTION_SIZE 14
# define APP_TITLE "Cub3D"

# define PIXEL_FACTOR 0.015625 // -> 1 / 64
# define M_PI 3.14159265358979323846
# define FOV_DEGREE 60
# define TILE_SIZE_INT 64
# define TILE_SIZE_DOUBLE 64.0

typedef enum e_wall_face
{
	WALL_NORTH,
	WALL_SOUTH,
	WALL_WEST,
	WALL_EAST
}					t_wall_face;

typedef struct s_ray
{
	double			x;
	double			y;
}					t_ray;

typedef struct s_casting_info
{
	int				hit;
	int				side;
	double			distanse;
	t_wall_face		face;
	t_ray			direction;
	t_ray			hit_position;
	t_ray			length;
}					t_casting_info;

typedef struct s_floor_view
{
	t_ray			ray_dir0;
	t_ray			ray_dir1;
	double			ray_dir_x0;
	double			ray_dir_y0;
	double			ray_dir_x1;
	double			ray_dir_y1;
}					t_floor_view;

typedef struct s_floor_row
{
	double			row_distance;
	t_ray			floor_setp;
	t_ray			floor_pos;
	double			floor_step_x;
	double			floor_step_y;
	double			floor_x;
	double			floor_y;
	double			factor;
}					t_floor_row;

typedef struct s_point
{
	int32_t			x;
	int32_t			y;
}					t_point;

typedef struct s_minimap_style
{
	int32_t			panel_size;
	uint32_t		color;
}					t_minimap_style;

typedef struct s_line_draw
{
	double			step_x;
	double			step_y;
	double			x;
	double			y;
	int32_t			steps;
}					t_line_draw;

typedef enum e_element
{
	NORTH_TEXTURE,
	SOUTH_TEXTURE,
	WEST_TEXTURE,
	EAST_TEXTURE,
	FLOOR_COLOR,
	CEILING_COLOR,
	ELEMENT_COUNT
}					t_element;

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

// cub3d
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
	uint8_t			elements_found[ELEMENT_COUNT];
	int32_t			player_start_x;
	int32_t			player_start_y;
	int8_t			player_start_dir;
}					t_map;

typedef struct s_parse_ctx
{
	int32_t			fd;
	t_map			*map;
	uint8_t			elements_found;
}					t_parse_ctx;

typedef struct s_player
{
	double			direction_radian;
	double			plane_radian;
	double			radian_shifting;
	double			len_to_screen;
	t_ray			origin;

}					t_player;

typedef struct s_images
{
	mlx_texture_t	*txt_no;
	mlx_texture_t	*txt_so;
	mlx_texture_t	*txt_ea;
	mlx_texture_t	*txt_we;
	mlx_texture_t	*txt_floor;
}					t_images;

typedef struct s_frames
{
	mlx_image_t		*sky_frame;
	mlx_image_t		*floor_frame;
	mlx_image_t		*walls_frame;
	mlx_image_t		*tools_frame;
}					t_frames;

// Image and img. It's bad naming
typedef struct s_app
{
	mlx_t			*mlx;
	t_map			*map;
	t_images		*img;
	bool			keys[6];
	int32_t			window_width;
	int32_t			window_height;
	double			last_time;

	t_frames		frames;
	t_player		player;
	t_casting_info	*temporary_info;
}					t_app;

// parsing
typedef struct s_map_lines_data
{
	char			***temp_map_lines;
	int32_t			*temp_map_height;
	int32_t			*temp_map_capacity;
}					t_map_lines_data;

typedef struct s_parse_file_data
{
	int32_t			fd;
	char			*line;
	char			*trimmed_line;
	char			*newline;
	bool			elements_fully_parsed;
	int32_t			i;
	bool			all_found;
}					t_parse_file_data;

// flood fill
typedef struct s_flood_fill_data
{
	int32_t			x;
	int32_t			y;
	int32_t			width;
	int32_t			height;
}					t_flood_fill_data;

typedef struct s_texture_element_args
{
	char			*key;
	char			*value;
	t_app			*app;
	int32_t			texture_type;
	char			**texture_path_ptr;
}					t_texture_element_args;

typedef struct s_color_element_args
{
	char			*key;
	char			*value;
	t_app			*app;
	int32_t			color_type;
	int32_t			*color_array;
}					t_color_element_args;

#endif
