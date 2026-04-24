
#include "cub3d.h"

void	put_pixel_safe_screen(t_app *app, t_point point, uint32_t color)
{
	if (point.x < 0 || point.y < 0 || point.x >= app->window_width
		|| point.y >= app->window_height)
		return ;
	mlx_put_pixel(app->frames.tools_frame, point.x, point.y, color);
}

void	put_minimap_pixel(t_app *app, t_point point, t_minimap_style style)
{
	if (point.x < MINIMAP_MARGIN + 2 || point.y < MINIMAP_MARGIN + 2)
		return ;
	if (point.x >= MINIMAP_MARGIN + style.panel_size - 2
		|| point.y >= MINIMAP_MARGIN + style.panel_size - 2)
		return ;
	put_pixel_safe_screen(app, point, style.color);
}

void	draw_rect(t_app *app, t_point point, int32_t size,
		t_minimap_style style)
{
	int32_t	draw_x;
	int32_t	draw_y;
	t_point	pixel;

	draw_y = 0;
	while (draw_y < size)
	{
		draw_x = 0;
		while (draw_x < size)
		{
			pixel.x = point.x + draw_x;
			pixel.y = point.y + draw_y;
			put_minimap_pixel(app, pixel, style);
			draw_x++;
		}
		draw_y++;
	}
}

void	draw_line(t_app *app, t_point start, t_point end,
		t_minimap_style style)
{
	t_line_draw	line;
	t_point		pixel;

	line.steps = ft_max(abs(end.x - start.x), abs(end.y - start.y));
	if (line.steps == 0)
		return ;
	line.step_x = (double)(end.x - start.x) / line.steps;
	line.step_y = (double)(end.y - start.y) / line.steps;
	line.x = start.x;
	line.y = start.y;
	style.color = get_rgba(255, 80, 80, 255);
	while (line.steps-- >= 0)
	{
		pixel.x = (int32_t)round(line.x);
		pixel.y = (int32_t)round(line.y);
		put_minimap_pixel(app, pixel, style);
		line.x += line.step_x;
		line.y += line.step_y;
	}
}
