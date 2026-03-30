#ifndef CUB3D_H
# define CUB3D_H

# include "defs.h"

void			exit_with_error(const char *message, t_app *app);
int32_t			get_rgba(int32_t r, int32_t g, int32_t b, int32_t a);
int32_t			get_texture_num(double ray_dir_x, double ray_dir_y,
					int32_t side);
int32_t			is_wall(t_app *app, double x, double y);
int32_t			validate_texture_file(const char *path);
const char		*get_parse_error_message(t_parse_error error);
t_parse_error	check_all_elements_found(t_parse_file_data *file_data,
					t_app *app);
bool			flood_fill(char **grid, t_flood_fill_data *data);
bool			flood_fill_recursive(char **grid, t_flood_fill_data *data);
t_parse_error	handle_color_element(const t_color_element_args *a);
t_parse_error	handle_texture_element(const t_texture_element_args *a);
t_parse_error	handle_texture_elements(char *line, char *value, t_app *app);
t_parse_error	parse_element(char *line, t_app *app);
t_parse_error	parse_map(t_app *app, const char *file);
t_parse_error	process_element_line(t_parse_file_data *file_data, t_app *app);
char			**str_array_dup(char **src, int32_t height);
char			*malloc_strdup(const char *src);
char			*ft_strpbrk(const char *s, const char *charset);
void			calculate_and_draw_wall(t_app *app, int32_t x,
					t_ray_data *ray_data);
void			calculate_texture_params(t_app *app, t_ray_data *ray);
void			calculate_wall_params(t_app *app, t_ray_data *ray);
void			cast_rays(t_app *app);
t_parse_error	check_walls_enclosed(t_app *app);
void			cleanup_graphics(t_app *app);
void			cleanup_textures(t_images *img);
void			draw_frame(t_app *app);
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
uint32_t		get_pixel(mlx_texture_t *texture, int32_t x, int32_t y);
uint32_t		get_texture_color(t_app *app, int32_t tex_num, int32_t tex_x,
					int32_t tex_y);

void			clean_exit(t_app *app);
void			print_parse_error(t_parse_error error);

void			setup_hooks(t_app *app);

#endif
