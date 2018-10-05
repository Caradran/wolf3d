/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:07:07 by esuits            #+#    #+#             */
/*   Updated: 2018/10/05 13:08:40 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		ray_in_scop(t_ray ray)
{
	if (ray.pos_x >= 0 && ray.pos_y >= 0 && ray.pos_x < 64
			&& ray.pos_y < 64)
		return (1);
	return (0);
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
