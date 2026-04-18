#include "cub3d.h"
#include <stdio.h>

static int32_t	__get_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | (uint32_t)a);
}

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

static void	drow_line_cast(t_app *app, int pixel, int x)
{
	int32_t		y;
	int32_t		y_end;
	uint32_t	color;

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
	while (y < y_end)
	{
		color = __get_rgba(0, 255, 0, 255);
		mlx_put_pixel(app->img->screen, x, y, color);
		y++;
	}
}

void	draw_wertical_line(t_app *app, t_casting_info info, int x)
{
	double	height;

	height = app->player.len_to_screen / info.distanse * 64.0;
	drow_line_cast(app, (int)height, x);
}

void	render_walls(t_app *app)
{
	int32_t			x;
	t_casting_info	info;

	x = 0;
	while (x < app->window_width)
	{
		info = start_casting(app, x);
		if (info.hit_gorisontal)
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
	draw_sky(app, ceiling_color);
	draw_floor(app);
	render_walls(app);
	render_minimap(app);
}