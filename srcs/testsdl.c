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

int		main(int argc, char **argv)
{
	t_env		env;
	SDL_Thread	*t;
	int			flag;
	int			color;
	SDL_Event	e;

	if (argc > 2 || argc <= 0)
		return (0);
	if (init_env(&env, argv, argc))
		return (0);
	color = 0;
	flag = 0;
	send_rays(&env);
	while (1)
	{
		while (flag || SDL_PollEvent(&e))
		{
			scan_keyboard(&env, e);
			move(&env);
			if (e.type == SDL_WINDOWEVENT
					&& e.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				rescale(&env);
				env.refresh = 1;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				flag = 1;
				color = choose_color(e, env, color);
			}
			if (e.type == SDL_MOUSEBUTTONUP)
				flag = 0;
			if (flag)
				draw_square_mouse(e, &env, color);
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) 
				ft_quit(&env, QUIT);
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
				if (save_map(env.map, "maps/map02"))
					ft_quit(&env, SAVE_FAIL);
			flag = 0;
		}
		flag = 1;
		if (env.refresh)
		{
			env.s = SDL_GetWindowSurface(env.w);
			bzero(env.s->pixels, sizeof(int) * env.s->w * env.s->h);
			if (argc == 1)
			{
				rescale(&env);
				draw_map(&env);
			}
			else
				send_rays(&env);
			SDL_UpdateWindowSurface(env.w);
			env.refresh = 0;
		}
	}
	SDL_Delay(10000);
	return (0);
}
