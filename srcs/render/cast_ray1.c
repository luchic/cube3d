#include "cub3d.h"

t_wall_face	get_wall_face(t_casting_info info)
{
	if (info.side == 0)
	{
		if (info.direction.x > 0)
			return (WALL_EAST);
		return (WALL_WEST);
	}
	if (info.direction.y > 0)
		return (WALL_SOUTH);
	return (WALL_NORTH);
}
