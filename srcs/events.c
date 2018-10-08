/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 18:26:40 by esuits            #+#    #+#             */
/*   Updated: 2018/10/07 18:26:43 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move(t_env *env)
{
	int rot;

	if (env->move)
	{
		if (!detect_collision(*env, env->move))
		{
			env->player.pos.x += env->player.dir.x * 0.05 * env->move;
			env->player.pos.y += env->player.dir.y * 0.05 * env->move;
			env->refresh = 1;
		}
	}
	if (env->rot)
	{
		rot = (env->move ? env->rot : env->rot * 2);
		env->player.dir = vec2_rot(rot * (double)M_PI /
			(360.0), env->player.dir);
		env->refresh = 1;
	}
}

void	set_move_flag(t_env *env, SDL_Event e, Uint8 *state)
{
	if (((state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) &&
		(state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])) ||
		(!(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) &&
		!(state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])))
		env->move = 0;
	else if ((state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]))
		env->move = 1;
	else if ((state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]))
		env->move = -1;
	if (abs(env->move) != 3 && state[SDL_SCANCODE_LSHIFT])
		env->move *= 3;
	else if (abs(env->move) == 3 && !state[SDL_SCANCODE_LSHIFT])
		env->move /= 3;
}

void	set_rot_flag(t_env *env, SDL_Event e, Uint8 *state)
{
	if ((state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) &&
		!(state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]))
		env->rot = 1;
	else if ((state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) &&
		!(state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]))
		env->rot = -1;
	else
		env->rot = 0;
	if (state[SDL_SCANCODE_LSHIFT])
		env->rot *= 2;
}

void	scan_mouse(t_env *env, SDL_Event e)
{
	static int	flag = 0;
	static int	color = 0;

	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		flag = 1;
		color = choose_color(e, *env, color);
	}
	if (e.type == SDL_MOUSEBUTTONUP)
		flag = 0;
	if (flag)
		draw_square_mouse(e, env, color);
}

void	scan_keyboard(t_env *env, SDL_Event e)
{
	Uint8 *state;

	state = (Uint8*)SDL_GetKeyboardState(NULL);
	if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN &&
		e.key.keysym.sym == SDLK_ESCAPE))
		ft_quit(env, QUIT);
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN && env->ed)
		if (save_map(env->map, MAPPATH))
			ft_quit(env, SAVE_FAIL);
	if (e.type == SDL_KEYUP || e.type == SDL_KEYDOWN || state[SDL_SCANCODE_UP]
		|| state[SDL_SCANCODE_W] || state[SDL_SCANCODE_DOWN] ||
		state[SDL_SCANCODE_S] || state[SDL_SCANCODE_LEFT] ||
		state[SDL_SCANCODE_A] || state[SDL_SCANCODE_RIGHT] ||
		state[SDL_SCANCODE_D] || state[SDL_SCANCODE_LSHIFT])
	{
		set_move_flag(env, e, state);
		set_rot_flag(env, e, state);
	}
}
