#include "wolf3d.h"

int main(int argc, char **argv)
{
	return (0);
}

int ceil(float x)
{
	if ((int)x == x)
		return ((int)x);
	return ((int)x + 1);
}

int floor(float x)
{
	return ((int)x);
}

float abs(float x)
{
	return(x >= 0 ? x : -x);
}

void	init_ray(t_ray *ray, t_player player,t_vec2 *dir)
{
	ray->side = 0;
	ray->pos_x = floor(player.x);
	ray->pos_y = floor(player.y);
	ray->delta.x = abs(1 / (float)player.dir.x);
	ray->delta.y = abs(1 / (float)player.dir.y);
	dir->x = 1;
	ray->dist.x = (1 + ray->pos_x - player.x) * ray->delta.x;
	if (player.dir.x < 0)
	{
		dir->x = -1;
		ray->dist.x = (player.x - ray->pos_x) * ray->delta.x;
	}
	dir->y = 1;
	ray->dist.y = (1 + ray->pos_y - player.y) * ray->delta.y;
	if (player.dir.y < 0)
	{
		dir->y = -1;
		ray->dist.y = (player.y - ray->pos_y) * ray->delta.y;
	}
}

t_vec2	init_vec2(float x, float y)
{
	return ((t_vec2){x, y});
}

t_ray intersect_wall(int **map, t_player player)
{
	int		hit_flag;
	t_ray	ray;
	t_vec2	dir;

	init_ray(&ray, player, &dir);
	hit_flag = 0;
	while (!hit_flag)
	{
		if (ray.dist.x < ray.dist.y)
		{
			ray.dist.x += ray.delta.x;
			ray.pos_x += dir.x;
			ray.side = 1;
		}
		else
		{
			ray.dist.y += ray.delta.y;
			ray.pos_y += dir.y;
			ray.side = 0;
		}
		if (ray.pos_x < 0 || ray.pos_x > 64 || ray.pos_y < 0 || ray.pos_y > 64)
		{
			ray.dist.x = -1;
			return (ray);
		}
		if (map[ray.pos_x][ray.pos_y])
			hit_flag = 1;
	}
	return (ray);
}