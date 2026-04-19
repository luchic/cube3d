#include "cub3d.h"
#include <stdio.h>


t_casting_info	start_casting(t_app *app, int x)
{
	double			radian;
	double			beta;
	t_ray			direction;
	t_casting_info	info;

	x = x - app->window_width / 2;
	beta = app->player.radian_shifting * x;
	radian = app->player.direction_radian + beta;
	direction = radian_to_vector(radian);
	info = cast_ray(app->map, app->player.origin, direction);
	info.distanse = info.distanse * cos(beta);
	return (info);
}

// static void	drow_line_cast(t_app *app, int pixel, int x)
// {
// 	int32_t		y;
// 	int32_t		y_end;
// 	uint32_t	color;

// 	if (pixel < app->window_height)
// 	{
// 		y = app->window_height / 2 - pixel / 2;
// 		y_end = app->window_height / 2 + pixel / 2;
// 	}
// 	else
// 	{
// 		y = 0;
// 		y_end = app->window_height;
// 	}
// 	while (y < y_end)
// 	{
// 		color = get_rgba(0, 255, 0, 255);
// 		mlx_put_pixel(app->img->screen, x, y, color);
// 		y++;
// 	}
// }

static int32_t get_texture_color(t_app *app, int cur, int max_height, int column)
{
	double tmp = (double)cur / (double) max_height;
	double tmp_y = tmp * 64.0;
	int tex_y = tmp_y;

	return (get_pixel(app->img->txt_no, column, tex_y));
}

static void	drow_line_from_texture(t_app *app, int pixel, int x, int text_pos)
{
	int32_t		y;
	int32_t		y_end;
	uint32_t	color;
	int tex_y;

	if (pixel < app->window_height)
	{
		y = app->window_height / 2 - pixel / 2;
		y_end = app->window_height / 2 + pixel / 2;
	}
	else
	{
		y = 0;
		y_end = app->window_height;
	}
	tex_y = 0;
	while (y < y_end)
	{
		color = get_texture_color(app, tex_y, pixel, text_pos);
		mlx_put_pixel(app->frames.walls_frame, x, y, color);
		y++;
		tex_y++;
	}
}

static int get_tex_x(t_casting_info info)
{
	double	wall_x;
	int		tex_x;
	int texture_width = 64;

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
	int texture_column;
	height = app->player.len_to_screen / info.distanse * 64.0;
	texture_column = get_tex_x(info);
	drow_line_from_texture(app, (int)height, x, texture_column);
}

void	clean_wall_frame(t_app *app)
{
	int color = get_rgba(0,0,0,0);
	for (int i = 0; i < app->window_height; i ++)
	{
		for (int j = 0; j < app->window_width; j ++)
			mlx_put_pixel(app->frames.walls_frame, j, i, color);
	}
}

void	render_walls(t_app *app)
{
	int32_t			x;
	t_casting_info	info;

	x = 0;
	clean_wall_frame(app);
	while (x < app->window_width)
	{
		info = start_casting(app, x);
		if (info.hit)
		{
			draw_wertical_line(app, info, x);
		}
		x++;
	}
}

void	re_draw(t_app *app)
{
	int32_t ceiling_color;

	if (!app || !app->img || !app->img->screen)
		return ;
	ceiling_color = get_rgba(app->map->ceiling_color[0],
			app->map->ceiling_color[1], app->map->ceiling_color[2], 255);
	// I don't need to recalculate it all the time. I need just another one layer
	// For my sky
	draw_sky(app, ceiling_color);
	draw_floor(app);
	render_walls(app);
	render_minimap(app);
}