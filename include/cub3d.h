/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:30:00 by nluchini          #+#    #+#             */
/*   Updated: 2026/04/13 15:46:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "defs.h"

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
void			draw_walls(t_app *app);
void			process_ray(t_app *app, int32_t x, t_ray_data *ray_data);
void			init_dda(t_app *app, t_ray_data *ray);
void			execute_dda(t_app *app, t_ray_data *ray);
void			calculate_and_draw_wall(t_app *app, int32_t x,
					t_ray_data *ray_data);
void			calculate_wall_params(t_app *app, t_ray_data *ray);
void			calculate_texture_params(t_app *app, t_ray_data *ray);
void			draw_vertical_strip(t_app *app, int32_t x, t_ray_data *ray);
int32_t			get_texture_num(double ray_dir_x, double ray_dir_y,
					int32_t side);
uint32_t		get_pixel(mlx_texture_t *texture, int32_t x, int32_t y);
uint32_t		get_texture_color(t_app *app, int32_t tex_num, int32_t tex_x,
					int32_t tex_y);
int32_t			get_rgba(int32_t r, int32_t g, int32_t b, int32_t a);
void			draw_sky(t_app *app, int32_t ceiling_color);
void			draw_floor(t_app *app);
void			init_floor_row(t_app *app, t_floor_view *view,
					t_floor_row *floor_row, int32_t y);
void			render_minimap(t_app *app);
void			put_pixel_safe_screen(t_app *app, t_point point,
					uint32_t color);
void			put_minimap_pixel(t_app *app, t_point point,
					t_minimap_style style);
void			draw_rect(t_app *app, t_point point, int32_t size,
					t_minimap_style style);
void			draw_line(t_app *app, t_point start, t_point end,
					t_minimap_style style);

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
