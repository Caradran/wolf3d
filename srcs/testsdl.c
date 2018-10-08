/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testsdl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:09:26 by esuits            #+#    #+#             */
/*   Updated: 2018/10/05 13:09:28 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	rescale(t_env *env)
{
	int scale;

	scale = (int)ft_min((int)env->s->w / 64, (int)env->s->h / 64);
	scale = (int)ft_min((env->s->w - 11 * scale) / 64, env->s->h / 64);
	scale = (scale < 3) ? 3 : scale;
	env->scale = scale;
	env->refresh = 1;
}

int		color_tile(int n)
{
	static int colors[NB_TILES + 1] =
	{0x555555, 0xffff00, 0x00ff00, 0xff0000, 0x0000ff, 0xffffff,
	0x123123, 0xff00ff, 0x000000, 0x542a10, 0x050555, 0xf0af0f,
	0x789789, 0x00ffff, 0xa0ffd0};

	return (colors[n]);
}

int		choose_color(SDL_Event e, t_env env, int prev)
{
	t_pos	pos;
	int		size;
	int		i;

	size = 2 * env.scale;
	pos.x = 68 * env.scale - 1;
	i = 0;
	while (i <= NB_TILES)
	{
		pos.y = (i + NB_TILES / 2) * env.scale * 32 / NB_TILES - 1;
		if (e.motion.x <= pos.x + size && e.motion.y <= pos.y + size &&
			e.motion.x >= pos.x && e.motion.y >= pos.y)
			return (i);
		i++;
	}
	return (prev);
}

void	refresh(t_env *env)
{
	env->s = SDL_GetWindowSurface(env->w);
	if (env->ed)
	{
		ft_memset(env->s->pixels, 0x0, sizeof(int) * env->s->w * env->s->h);
		rescale(env);
		draw_map(env);
	}
	else
	{
		ft_memset(env->s->pixels, 0xb0,
			(sizeof(int) * env->s->w * env->s->h) / 2);
		ft_memset(&(env->s->pixels[(sizeof(int) * env->s->w * env->s->h)
			/ 2]), 0x00, (sizeof(int) * env->s->w * env->s->h) / 2);
		send_rays(env);
	}
	SDL_UpdateWindowSurface(env->w);
	env->refresh = 0;
}

int		main(int argc, char **argv)
{
	t_env		env;
	int			flag;
	SDL_Event	e;

	if (argc > 3 || argc <= 0 || (argc == 3 && ft_strcmp(argv[2], "ed"))
		|| init_env(&env, argv, argc))
		return (write(0, "usage : wolf3d [map [ed]]\n", 26));
	while (1)
	{
		flag = 1;
		while (flag || SDL_PollEvent(&e))
		{
			if (env.ed)
				scan_mouse(&env, e);
			scan_keyboard(&env, e);
			move(&env);
			if (e.type == SDL_WINDOWEVENT
					&& e.window.event == SDL_WINDOWEVENT_RESIZED)
				rescale(&env);
			flag = 0;
		}
		if (env.refresh)
			refresh(&env);
	}
	return (0);
}
