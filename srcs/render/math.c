#include "cub3d.h"

t_ray	sub(t_ray a, t_ray b)
{
	a.x -= b.x;
	a.y -= b.y;
	return (a);
}

t_ray	floor_ray(t_ray ray)
{
	ray.x = floor(ray.x);
	ray.y = floor(ray.y);
	return (ray);
}

t_ray	sign(t_ray ray)
{
	if (ray.x < 0)
		ray.x = -1;
	else
		ray.x = 1;
	if (ray.y < 0)
		ray.y = -1;
	else
		ray.y = 1;
	return (ray);
}

double	get_radian(double angle)
{
	return (M_PI * (2.0 - angle / 180.0));
}
