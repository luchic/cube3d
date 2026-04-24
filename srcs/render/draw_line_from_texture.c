#include "cub3d.h"

static int32_t	get_texture_color(t_app *app, int relative, int max_height,
		int texture_x)
{
	double	texture_y;

	texture_y = (double)relative / (double)max_height * TILE_SIZE_DOUBLE;
	if (app->temporary_info->face == WALL_EAST)
		return (get_pixel(app->img->txt_ea, texture_x, texture_y));
	else if (app->temporary_info->face == WALL_WEST)
		return (get_pixel(app->img->txt_we, texture_x, texture_y));
	else if (app->temporary_info->face == WALL_SOUTH)
		return (get_pixel(app->img->txt_so, texture_x, texture_y));
	else
		return (get_pixel(app->img->txt_no, texture_x, texture_y));
}

static void	drow_line_from_texture(t_app *app, int wall_height, int x,
		int texture_x)
{
	int			draw_start;
	int			draw_end;
	int			wall_top;
	int			wall_bottom;
	uint32_t	color;

	wall_top = app->window_height / 2 - wall_height / 2;
	wall_bottom = app->window_height / 2 + wall_height / 2;
	draw_start = wall_top;
	draw_end = wall_bottom;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end > app->window_height)
		draw_end = app->window_height;
	while (draw_start < draw_end)
	{
		color = get_texture_color(app, draw_start - wall_top, wall_height,
				texture_x);
		mlx_put_pixel(app->frames.walls_frame, x, draw_start, color);
		draw_start++;
	}
}

static inline int	get_tex_x(t_casting_info info)
{
	double	wall_x;
	int		tex_x;
	int		texture_width;

	texture_width = TILE_SIZE_INT;
	if (info.side == 0)
		wall_x = info.hit_position.y;
	else
		wall_x = info.hit_position.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * texture_width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture_width)
		tex_x = texture_width - 1;
	return (tex_x);
}

void	draw_wertical_line(t_app *app, t_casting_info info, int x)
{
	double	height;
	int		texture_column;

	height = app->player.len_to_screen / info.distanse * TILE_SIZE_DOUBLE;
	texture_column = get_tex_x(info);
	app->temporary_info = &info;
	drow_line_from_texture(app, (int)height, x, texture_column);
}
