#include "cub3d.h"
#include <stdio.h>


t_casting_info	start_casting(t_app *app, int x)
{
	double			plane_scale;
	double			beta;
	t_ray			direction;
	t_ray			plane;
	t_casting_info	info;

	direction = radian_to_vector(app->player.direction_radian);
	plane = radian_to_vector(app->player.plane_radian);
	plane_scale = 2.0 * x / (double)app->window_width - 1.0;
	plane.x *= (plane_scale * tan((FOV_DEGREE / 2.0) * M_PI / 180.0));
	plane.y *= (plane_scale * tan((FOV_DEGREE / 2.0) * M_PI / 180.0));
	direction.x += plane.x;
	direction.y += plane.y;
	info = cast_ray(app->map, app->player.origin, direction);
	beta = ((double)x - (double)app->window_width / 2)
		* app->player.radian_shifting;
	info.distanse = info.distanse * cos(beta);
	return (info);
}

// t_casting_info	start_casting(t_app *app, int x)
// {
// 	double			radian;
// 	double			beta;
// 	t_ray			direction;
// 	t_casting_info	info;

// 	x = x - app->window_width / 2;
// 	beta = app->player.radian_shifting * x;
// 	radian = app->player.direction_radian + beta;
// 	direction = radian_to_vector(radian);
// 	info = cast_ray(app->map, app->player.origin, direction);
// 	info.distanse = info.distanse * cos(beta);
// 	return (info);
// }

/*
t_casting_info	start_casting(t_app *app, int x)
{
	t_ray			direction;
	t_ray			plane;
	double			camera_x;
	double			ray_length;
	t_casting_info	info;

	direction = radian_to_vector(app->player.direction_radian);
	plane = radian_to_vector(app->player.plane_radian);
	
	camera_x = 2.0 * x / (double)app->window_width - 1.0;
	plane.x *= tan((FOV_DEGREE / 2.0) * M_PI / 180.0) * camera_x;
	plane.y *= tan((FOV_DEGREE / 2.0) * M_PI / 180.0) * camera_x;
	direction.x += plane.x;
	direction.y += plane.y;
	ray_length = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction.x /= ray_length;
	direction.y /= ray_length;
	info = cast_ray(app->map, app->player.origin, direction);
	info.distanse /= ray_length;
	return (info);
}*/

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

static int32_t get_texture_color(t_app *app, int relative, int max_height, int texture_x)
{
	double texture_y;

	texture_y = (double) relative / (double) max_height * TILE_SIZE_DOUBLE;
	return (get_pixel(app->img->txt_no, texture_x, texture_y));
}

static void	drow_line_from_texture(t_app *app, int wall_height, int x, int texture_x)
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
		color = get_texture_color(app, draw_start - wall_top, wall_height, texture_x);
		mlx_put_pixel(app->frames.walls_frame, x, draw_start, color);
		draw_start++;
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
	int	color;
	int	i;
	int	j;

	color = get_rgba(0,0,0,0);
	i = 0;
	while (i < app->window_height)
	{
		j = 0;
		while (j < app->window_width)
		{
			mlx_put_pixel(app->frames.walls_frame, j, i, color);
			j++;
		}
		i++;
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

	if (!app || !app->img)
		return ;
	ceiling_color = get_rgba(app->map->ceiling_color[0],
			app->map->ceiling_color[1], app->map->ceiling_color[2], 255);
	// draw_sky(app, ceiling_color);
	draw_floor(app);
	render_walls(app);
	render_minimap(app);
}
