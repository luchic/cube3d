#include "cub3d.h"

int32_t	get_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((uint32_t)r << 24
		| (uint32_t)g << 16
		| (uint32_t)b << 8
		| (uint32_t)a);
}
