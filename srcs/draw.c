/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 18:23:41 by esuits            #+#    #+#             */
/*   Updated: 2018/10/07 18:23:43 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_legend(t_env *env)
{
	int i;

	i = 0;
	while (i <= NB_TILES)
	{
		set_square(2 * env->scale, 0xffffff, (t_pos){68 * env->scale - 1,
			(i + NB_TILES / 2) * env->scale * 32 / NB_TILES - 1}, env->s);
		set_square(2 * env->scale - 2, color_tile(i), (t_pos){68 * env->scale,
			(i + NB_TILES / 2) * env->scale * 32 / NB_TILES}, env->s);
		i++;
	}
}

void	draw_map(t_env *env)
{
	int i;
	int j;

	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			if (i == 0 || j == 0 || i == 63 || j == 63)
				set_square(env->scale - 1, color_tile(NB_TILES), (t_pos){i *
					env->scale, j * env->scale}, env->s);
			else if (env->map[j][i] >= 0 && env->map[j][i] <= NB_TILES)
				set_square(env->scale - 1, color_tile(env->map[j][i]),
					(t_pos){i * env->scale, j * env->scale}, env->s);
			j++;
		}
		i++;
	}
	draw_legend(env);
}

void	draw_square_mouse(SDL_Event e, t_env *env, int flag)
{
	if (e.motion.x / env->scale < 63 && e.motion.y / env->scale < 63 &&
		e.motion.x / env->scale > 0 && e.motion.y / env->scale > 0)
	{
		env->map[((int)(e.motion.y / env->scale))]
				[((int)(e.motion.x / env->scale))] = flag;
		env->refresh = 1;
	}
}

t_text	choose_text(t_env *env, t_ray ray)
{
	if (ray.side && ray.dir.x == 1)
		return (env->texts[env->map[ray.pos_x][ray.pos_y] % (NB_TEXT)]);
	if (ray.side && ray.dir.x == -1)
		return (env->texts[(env->map[ray.pos_x][ray.pos_y] + 1) % (NB_TEXT)]);
	if (!ray.side && ray.dir.y == 1)
		return (env->texts[(env->map[ray.pos_x][ray.pos_y] + 2) % (NB_TEXT)]);
	return (env->texts[(env->map[ray.pos_x][ray.pos_y] + 3) % (NB_TEXT)]);
}

void	print_wall(t_ray ray, t_env *env, int i, t_vec2 dir)
{
	double	dist;
	double	rh;
	double	hight;
	int		j;
	t_text	text;

	dist = wall_dist(ray, env->player, dir);
	rh = env->s->h / (dist * cos(-FOV / 2.0 + (double)i / env->s->w) * FOV);
	j = -1;
	text = choose_text(env, ray);
	hight = dir.x < 0 ? part_dec(env->player.pos.y + dist * dir.y) :
	1 - part_dec(env->player.pos.y + dist * dir.y);
	dir.x = (dir.y > 0 ? part_dec(env->player.pos.x + dist * dir.x) :
		1 - part_dec(env->player.pos.x + dist * dir.x));
	dir.y = hight;
	hight = (rh > env->s->h ? env->s->h : rh);
	while (++j < (int)hight)
		if (ray_in_scop(ray) && ray.side)
			set_pixel((t_pos){i, ((env->s->h - (int)hight) / 2 + j)}, uv_wall(
		text, (double)((j - (double)(hight - rh) / 2) / rh), dir.y), env->s);
		else if (ray_in_scop(ray))
			set_pixel((t_pos){i, ((env->s->h - hight) / 2 + j)},
			uv_wall(text, (double)j / rh -
			(double)(hight - rh) / (2 * rh), dir.x), env->s);
}
