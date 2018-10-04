#include "wolf3d.h"

t_ray	init_ray(t_player player)
{
	t_ray ray;

	ray.side = 0;
	ray.pos_x = ft_floor(player.pos.x);
	ray.pos_y = ft_floor(player.pos.y);
	ray.delta.x = ft_abs(1 / (double)player.dir.x);
	ray.delta.y = ft_abs(1 / (double)player.dir.y);
	ray.dir.x = 1;
	ray.dist.x = (1 + ray.pos_x - player.pos.x) * ray.delta.x;
	if (player.dir.x < 0)
	{
		ray.dir.x = -1;
		ray.dist.x = (player.pos.x - ray.pos_x) * ray.delta.x;
	}
	ray.dir.y = 1;
	ray.dist.y = (1 + ray.pos_y - player.pos.y) * ray.delta.y;
	if (player.dir.y < 0)
	{
		ray.dir.y = -1;
		ray.dist.y = (player.pos.y - ray.pos_y) * ray.delta.y;
	}
	return (ray);
}

t_ray	intersect_wall(int **map, t_player player, t_ray ray)
{
	while (!map[ray.pos_x][ray.pos_y])
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
		if (ray.pos_x < 0 || ray.pos_x >= 64 || ray.pos_y < 0
			|| ray.pos_y >= 64)
		{
			ray.dist.x = -1;
			return (ray);
		}
	}
	return (ray);
}

double	wall_dist(t_ray ray, t_player player, t_vec2 dir)
{
	double dist;

	if (ray.side)
		dist = (ray.pos_x - player.pos.x + (1 - ray.dir.x) / 2) / dir.x;
	else
		dist = (ray.pos_y - player.pos.y + (1 - ray.dir.y) / 2) / dir.y;
	return (dist);
}

void	print_wall(t_ray ray, t_env *env, int i, t_vec2 dir)
{
	double	dist;
	double	re_hight;
	double	hight;
	int		j;
	t_text  text;

	dist = wall_dist(ray, env->player, dir);
	re_hight = env->s->h / (dist * cos(-FOV / 2.0 + (double)i / env->s->w) * FOV);
	hight = env->s->h / ((dist * cos(-FOV / 2.0 + ((double)i / env->s->w) * FOV)) < 1 ? 1 : (dist * cos(-FOV / 2.0 + ((double)i / env->s->w) * FOV)));
	j = -1;
	text = env->texts[env->map[ray.pos_x][ray.pos_y] % (NB_TEXT)];
	while (++j < (int)hight)
		if (ray.pos_x >= 0 && ray.pos_y >= 0 && ray.pos_x < 64
			&& ray.pos_y < 64 && ray.side)
			set_pixel((t_pos){i, ((env->s->h - (int)hight) / 2 + j)},
				uv_wall(text, (double)j / re_hight - (double)(hight - re_hight) / (2 * re_hight), env->player.pos.y + dist * dir.y - (int)(env->player.pos.y + dist * dir.y)), env->s);
		else if (ray.pos_x >= 0 && ray.pos_y >= 0 && ray.pos_x < 64
			&& ray.pos_y < 64)
			set_pixel((t_pos){i, ((env->s->h - hight) / 2 + j)},
				scale_color(uv_wall(text, (double)j / re_hight - (double)(hight - re_hight) / (2 * re_hight), env->player.pos.x + dist * dir.x - (int)(env->player.pos.x + dist * dir.x)), 0.5), env->s);
}

void	send_rays(t_env *env)
{
	t_ray		ray;
	t_vec2		dir;
	int			i;
	double		angle;
	t_player	tmpplayer;

	dir = env->player.dir;
	tmpplayer = env->player;
	i = 0;
	while (i < env->s->w)
	{
		angle = -FOV / 2.0 + ((double)i / env->s->w) * FOV;
		tmpplayer.dir = vec2_rot(-angle, dir);
		ray = intersect_wall(env->map, env->player, init_ray(tmpplayer));
		if (ray.dist.x != -1)
			print_wall(ray, env, i, tmpplayer.dir);
		i++;
	}
}
