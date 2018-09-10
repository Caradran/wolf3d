#include "wolf3d.h"

int main(int argc, char **argv)
{
	return (0);
}

void	init_ray(t_ray *ray, t_player player)
{
	ray->side = 0;
	ray->pos_x = floor(player.x);
	ray->pos_y = floor(player.y);
	ray->delta.x = abs(1 / (float)player.dir.x);
	ray->delta.y = abs(1 / (float)player.dir.y);
	ray->dir.x = 1;
	ray->dist.x = (1 + ray->pos_x - player.x) * ray->delta.x;
	if (player.dir.x < 0)
	{
		ray->dir.x = -1;
		ray->dist.x = (player.x - ray->pos_x) * ray->delta.x;
	}
	ray->dir.y = 1;
	ray->dist.y = (1 + ray->pos_y - player.y) * ray->delta.y;
	if (player.dir.y < 0)
	{
		ray->dir.y = -1;
		ray->dist.y = (player.y - ray->pos_y) * ray->delta.y;
	}
}

t_ray intersect_wall(int **map, t_player player)
{
	t_ray	ray;

	init_ray(&ray, player);
	while (1)
	{
		ray.side = (ray.dist.x < ray.dist.y);
		if (ray.side)
		{
			ray.dist.x += ray.delta.x;
			ray.pos_x += ray.dir.x;
		}
		else
		{
			ray.dist.y += ray.delta.y;
			ray.pos_y += ray.dir.y;
		}
		if (ray.pos_x < 0 || ray.pos_x > 64 || ray.pos_y < 0 || ray.pos_y > 64)
		{
			ray.dist.x = -1;
			return (ray);
		}
		if (map[ray.pos_x][ray.pos_y])
			break;
	}
	return (ray);
}