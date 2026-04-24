
#ifndef CUB3D_H
# define CUB3D_H

# include "defs.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

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

// parsing
t_parse_error	parse_map(t_app *app, const char *file);
t_parse_error	parse_element(char *line, t_parse_ctx *ctx);
t_parse_error	parse_grid(t_parse_ctx *ctx, char *first_line);
t_parse_error	validate_map(t_map *map);
t_parse_error	pad_grid(t_map *map);
void			debug_print_map(t_map *map);

// parsing error
void			print_parse_error(t_parse_error error);

// utils
void			exit_with_error(const char *message, t_app *app);
char			*malloc_strdup(const char *src);
char			**str_array_dup(char **src, int32_t height);
int32_t			validate_texture_file(const char *path);
char			*ft_strpbrk(const char *s, const char *charset);
int				is_empty_line(char *line);
int				check_extension(const char *file, const char *ext);

//==============================================================================
//                        mlx
//==============================================================================

void			setup_graphics(t_app *app);
void			setup_hooks(t_app *app);
int				load_textures(t_app *app);
void			cleanup_textures(t_images *img);
void			cleanup_graphics(t_app *app);
int				init_frames(t_app *app);

//==============================================================================
//                       cast rays
//==============================================================================

t_ray			sub(t_ray a, t_ray b);
t_ray			floor_ray(t_ray ray);
t_ray			sign(t_ray ray);
double			get_radian(double angle);
t_ray			radian_to_vector(double radian);
t_casting_info	cast_ray(t_map *map, t_ray origin, t_ray direction);

//==============================================================================
//                       render
//==============================================================================

void			render(t_app *app);
int32_t			get_texture_num(double ray_dir_x, double ray_dir_y,
					int32_t side);
uint32_t		get_pixel(mlx_texture_t *texture, int32_t x, int32_t y);
int32_t			get_rgba(int32_t r, int32_t g, int32_t b, int32_t a);
void			draw_sky(t_app *app, int32_t ceiling_color);
void			draw_floor(t_app *app);
void			render_minimap(t_app *app);
void			put_pixel_safe_screen(t_app *app, t_point point,
					uint32_t color);
void			put_minimap_pixel(t_app *app, t_point point,
					t_minimap_style style);
void			draw_rect(t_app *app, t_point point, int32_t size,
					t_minimap_style style);
void			draw_line(t_app *app, t_point start, t_point end,
					t_minimap_style style);
void			re_draw(t_app *app);


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
t_parse_error	handle_color_element(const t_color_element_args *a);

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

//==============================================================================l
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
