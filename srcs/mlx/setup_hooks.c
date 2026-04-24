#include "cub3d.h"

static void	main_loop_hook(void *param)
{
	t_app	*app;
	double	now;

	app = param;
	movehook(app);
	handle_movement(app);
	now = mlx_get_time();
	if (now - app->last_time < 0.03)
		return ;
	render(app);
	app->last_time = now;
}

static void resize_frames(t_app *app)
{
	mlx_delete_image(app->mlx, app->frames.floor_frame);
	mlx_delete_image(app->mlx, app->frames.sky_frame);
	mlx_delete_image(app->mlx, app->frames.tools_frame);
	mlx_delete_image(app->mlx, app->frames.walls_frame);

	init_frames(app);
}

static void	resize_callback(int32_t width, int32_t height, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (!app || !app->img)
		return ;
	app->window_width = width;
	app->window_height = height;
	app->player.radian_shifting = (FOV_DEGREE / 180.0 * M_PI) / (double)width;
	resize_frames(app);
}

void	setup_hooks(t_app *app)
{
	mlx_resize_hook(app->mlx, resize_callback, app);
	mlx_loop_hook(app->mlx, main_loop_hook, app);
}
