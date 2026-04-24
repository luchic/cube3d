/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:32:30 by sruff             #+#    #+#             */
/*   Updated: 2026/04/24 15:33:06 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "../mlx42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

<<<<<<< HEAD
# define ELEM_NO 0x01
# define ELEM_SO 0x02
# define ELEM_WE 0x04
# define ELEM_EA 0x08
# define ELEM_F 0x10
# define ELEM_C 0x20
# define ELEM_ALL 0x3F

// Assets
// Grid
// Plazer

// parsing_output

typedef struct s_map
{
	char		**grid;
	int32_t		grid_width;
	int32_t		grid_height;
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	char		*east_texture_path;
	int32_t		floor_color[3];
	int32_t		ceiling_color[3];
	int32_t		player_start_x;
	int32_t		player_start_y;
	int8_t		player_start_dir;
}				t_map;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
}				t_player;

typedef struct s_app
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_map		*map;
	t_player	player;
	int32_t		window_width;
	int32_t		window_height;
}				t_app;

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
}				t_parse_error;

// parsing
t_parse_error	parse_map(t_app *app, const char *file);
t_parse_error	parse_element(char *line, t_parse_ctx *ctx);
t_parse_error	parse_grid(t_parse_ctx *ctx, char *first_line);
t_parse_error	validate_map(t_map *map);
t_parse_error	pad_grid(t_map *map);
void			debug_print_map(t_map *map);

// parsing error
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

int32_t			get_rgba(int32_t r, int32_t g, int32_t b, int32_t a);
int32_t			get_texture_num(double ray_dir_x, double ray_dir_y,
					int32_t side);
int32_t			is_wall(t_app *app, double x, double y);
int32_t			parse_map(t_app *app, const char *file);
int32_t			validate_texture_file(const char *path);
bool			check_all_elements_found(t_parse_file_data *file_data,
					t_app *app);
bool			flood_fill(char **grid, t_flood_fill_data *data);
bool			flood_fill_recursive(char **grid, t_flood_fill_data *data);
bool			handle_color_element(const t_color_element_args *a);
bool			handle_texture_element(const t_texture_element_args *a);
bool			handle_texture_elements(char *line, char *value, t_app *app);
bool			parse_element(char *line, t_app *app);
bool			process_element_line(t_parse_file_data *file_data, t_app *app);
void			exit_with_error(const char *message, t_app *app);
int32_t			get_rgba(int32_t r, int32_t g, int32_t b, int32_t a);
int32_t			get_texture_num(double ray_dir_x, double ray_dir_y,
					int32_t side);
int32_t			is_wall(t_app *app, double x, double y);
int32_t			validate_texture_file(const char *path);
int32_t			count_str_array(char **values);
const char		*get_parse_error_message(t_parse_error error);
t_parse_error	check_all_elements_found(t_parse_file_data *file_data,
					t_app *app);
bool			flood_fill(char **grid, t_flood_fill_data *data);
bool			flood_fill_recursive(char **grid, t_flood_fill_data *data);
t_parse_error	assign_color_values(char **rgb_values, int32_t color[3]);
t_parse_error	check_valid_color_format(char *str);
t_parse_error	validate_and_assign_color_component(char *str_val,
					int32_t *color_component);
t_parse_error	handle_color_element(const t_color_element_args *a);
t_parse_error	handle_empty_line(t_parse_file_data *file_data, t_app *app,
					int32_t *consecutive_empty_lines,
					t_map_lines_data *map_data);
t_parse_error	handle_texture_element(const t_texture_element_args *a);
t_parse_error	handle_texture_elements(char *line, char *value, t_app *app);
t_parse_error	handle_file_line(t_parse_file_data *file_data, t_app *app,
					int32_t *consecutive_empty_lines,
					t_map_lines_data *map_data);
t_parse_error	init_file_read(const char *filename,
					t_parse_file_data *file_data, t_map_lines_data *map_data);
t_parse_error	finalize_parsed_map(t_parse_file_data *file_data, t_app *app,
					char **temp_map_lines, int32_t temp_map_height);
t_parse_error	parse_element(char *line, t_app *app);
t_parse_error	parse_map(t_app *app, const char *file);
t_parse_error	pad_map_line(t_map *map, int32_t i);
t_parse_error	process_element_line(t_parse_file_data *file_data, t_app *app);

t_parse_error	process_valid_line(t_parse_file_data *file_data, t_app *app,
					t_map_lines_data *map_data);

char			**str_array_dup(char **src, int32_t height);
char			*malloc_strdup(const char *src);
char			*ft_strpbrk(const char *s, const char *charset);
void			calculate_and_draw_wall(t_app *app, int32_t x,
					t_ray_data *ray_data);

void			calculate_texture_params(t_app *app, t_ray_data *ray);
void			calculate_wall_params(t_app *app, t_ray_data *ray);
void			cast_rays(t_app *app);
void			check_walls_enclosed(t_app *app);
void			cleanup_mlx(t_app *app);
void			calculate_texture_params(t_app *app, t_ray_data *ray);

//==============================================================================
//                        mlx   
//==============================================================================

void			setup_graphics(t_app *app);
void			setup_hooks(t_app *app);
int				load_textures(t_app *app);
void			cleanup_textures(t_images *img);
void			cleanup_graphics(t_app *app);

//==============================================================================
//                       render   
//==============================================================================

void			render(t_app *app);
void			draw_frame(t_app *app);
void			cast_rays(t_app *app);
void			process_ray(t_app *app, int32_t x, t_ray_data *ray_data);
void			init_dda(t_app *app, t_ray_data *ray);
void			execute_dda(t_app *app, t_ray_data *ray);
void			calculate_and_draw_wall(t_app *app, int32_t x,
					t_ray_data *ray_data);

void			calculate_wall_params(t_app *app, t_ray_data *ray);
void			calculate_texture_params(t_app *app, t_ray_data *ray);
void			draw_vertical_strip(t_app *app, int32_t x, t_ray_data *ray);
void			execute_dda(t_app *app, t_ray_data *ray);
void			handle_movement(t_app *app);
void			init_dda(t_app *app, t_ray_data *ray);

void			create_screen_image(t_app *app);
void			init_player(t_app *app);
int				load_textures(t_app *app);
void			setup_graphics(t_app *app);
void			move_forward_backward(t_app *app, double move_dir);
void			move_strafe(t_app *app, double strafe_dir);
void			movehook(void *param);
t_parse_error	pad_map_grid(t_app *app);
t_parse_error	parse_color(char *line, int32_t color[3], t_app *app);
t_parse_error	process_file_lines(t_parse_file_data *file_data, t_app *app,
					t_map_lines_data *map_data);
void			process_ray(t_app *app, int32_t x, t_ray_data *ray_data);
t_parse_error	read_and_parse_file(const char *filename, t_app *app);
void			render(t_app *app);
t_parse_error	validate_map(t_app *app);

int32_t			get_texture_num(double ray_dir_x, double ray_dir_y,
					int32_t side);

uint32_t		get_pixel(mlx_texture_t *texture, int32_t x, int32_t y);
uint32_t		get_texture_color(t_app *app, int32_t tex_num, int32_t tex_x,
					int32_t tex_y);
int32_t			get_rgba(int32_t r, int32_t g, int32_t b, int32_t a);
void			draw_ceiling(t_app *app, int32_t ceiling_color);
void			draw_floor(t_app *app, int32_t floor_color);
void			init_floor_row(t_app *app, t_floor_view *view,
					t_floor_row *floor_row, int32_t y);

//==============================================================================
//                       parse   
//==============================================================================

t_parse_error	parse_map(t_app *app, const char *file);
t_parse_error	read_and_parse_file(const char *filename, t_app *app);
t_parse_error	init_file_read(const char *filename,
					t_parse_file_data *file_data, t_map_lines_data *map_data);
t_parse_error	process_file_lines(t_parse_file_data *file_data, t_app *app,
					t_map_lines_data *map_data);
t_parse_error	handle_file_line(t_parse_file_data *file_data, t_app *app,
					int32_t *consecutive_empty_lines,
					t_map_lines_data *map_data);
t_parse_error	handle_empty_line(t_parse_file_data *file_data, t_app *app,
					int32_t *consecutive_empty_lines,
					t_map_lines_data *map_data);
t_parse_error	process_valid_line(t_parse_file_data *file_data, t_app *app,
					t_map_lines_data *map_data);
t_parse_error	process_element_line(t_parse_file_data *file_data, t_app *app);
t_parse_error	finalize_parsed_map(t_parse_file_data *file_data, t_app *app,
					char **temp_map_lines, int32_t temp_map_height);
t_parse_error	parse_element(char *line, t_app *app);
t_parse_error	handle_texture_element(const t_texture_element_args *a);
t_parse_error	handle_texture_elements(char *line, char *value, t_app *app);
t_parse_error	handle_color_element(const t_color_element_args *a);
t_parse_error	parse_color(char *line, int32_t color[3], t_app *app);
t_parse_error	check_valid_color_format(char *str);
t_parse_error	validate_and_assign_color_component(char *str_val,
					int32_t *color_component);
t_parse_error	assign_color_values(char **rgb_values, int32_t color[3]);
int32_t			count_str_array(char **values);
t_parse_error	pad_map_grid(t_app *app);
t_parse_error	pad_map_line(t_map *map, int32_t i);
t_parse_error	check_all_elements_found(t_parse_file_data *file_data,
					t_app *app);

//==============================================================================
//                        player   
//==============================================================================

void			init_player(t_app *app);
void			handle_movement(t_app *app);
void			movehook(void *param);
void			move_forward_backward(t_app *app, double move_dir);
void			move_strafe(t_app *app, double strafe_dir);

//==============================================================================
//                        validate   
//==============================================================================

t_parse_error	validate_map(t_app *app);
t_parse_error	check_walls_enclosed(t_app *app);
bool			flood_fill(char **grid, t_flood_fill_data *data);
bool			flood_fill_recursive(char **grid, t_flood_fill_data *data);

//==============================================================================
//                        tools   
//==============================================================================

void			exit_with_error(const char *message, t_app *app);
void			clean_exit(t_app *app);
void			print_parse_error(t_parse_error error);
const char		*get_parse_error_message(t_parse_error error);
char			*malloc_strdup(const char *src);
char			**str_array_dup(char **src, int32_t height);
char			*ft_strpbrk(const char *s, const char *charset);
int32_t			validate_texture_file(const char *path);

#endif
