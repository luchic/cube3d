
#include "cub3d.h"

void	clean_exit(t_app *app)
{
	cleanup_graphics(app);
	ft_clean();
	exit(1);
}

void	exit_with_error(const char *message, t_app *app)
{
	ft_printf("Error: %s\n", message);
	if (app)
	{
		if (app->mlx)
			mlx_terminate(app->mlx);
	}
	ft_clean();
	exit(1);
}
