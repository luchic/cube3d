#include "cub3d.h"

void	process_ray(t_app *app, int32_t x, t_ray_data *ray_data)
{
	ray_data->camera_x = 2 * x / (double)app->window_width - 1;
	ray_data->ray_dir_x = app->player.dir_x + app->player.plane_x
		* ray_data->camera_x;
	ray_data->ray_dir_y = app->player.dir_y + app->player.plane_y
		* ray_data->camera_x;
	ray_data->delta_dist_x = fabs(1 / ray_data->ray_dir_x);
	ray_data->delta_dist_y = fabs(1 / ray_data->ray_dir_y);
	ray_data->hit = 0;
	init_dda(app, ray_data);
	execute_dda(app, ray_data);
	if (ray_data->hit == 0)
		return ;
	calculate_and_draw_wall(app, x, ray_data);
}

void	init_floor_row(t_app *app, t_floor_view *view,
		t_floor_row *floor_row, int32_t y)
{
	floor_row->row_distance = (0.5 * app->window_height)
		/ (y - app->window_height / 2);
	floor_row->floor_step_x = floor_row->row_distance
		* (view->ray_dir_x1 - view->ray_dir_x0) / app->window_width;
	floor_row->floor_step_y = floor_row->row_distance
		* (view->ray_dir_y1 - view->ray_dir_y0) / app->window_width;
	floor_row->floor_x = app->player.pos_x + floor_row->row_distance
		* view->ray_dir_x0;
	floor_row->floor_y = app->player.pos_y + floor_row->row_distance
		* view->ray_dir_y0;
	floor_row->factor = (double)(y - app->window_height / 2)
		/ (app->window_height / 2);
}
