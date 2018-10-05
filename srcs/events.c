#include "wolf3d.h"

int		detect_collision(t_env env, int dir)
{
	int x;
	int y;
	int supp;

	x = env.player.pos.x + 0.05 * dir * env.player.dir.x;
	y = env.player.pos.y + 0.05 * dir * env.player.dir.y;
	supp = 0;
	if (fabs(env.player.dir.x) > fabs(env.player.dir.y))
		supp = 1;
	if (x < 0 || x > 64 || y < 0 || y > 64 || env.map[x][y])
		return (1);
	else if ((x != (int)env.player.pos.x && y != (int)env.player.pos.y) &&
		supp && env.map[x][y - sign(dir * env.player.dir.y)])
		return (1);
	else if ((x != (int)env.player.pos.x && y != (int)env.player.pos.y) &&
		!supp && env.map[x - sign(dir * env.player.dir.x)][y])
		return (1);
	return (0);
}

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
		env->player.dir = vec2_rot(rot * (double)M_PI / (3 * 180.0), env->player.dir);
		env->refresh = 1;
	}
}

void	set_move_flag(t_env *env, SDL_Event e, Uint8 *state)
{
	printf("%i ", state[SDL_SCANCODE_UP]);
	printf("%i ", env->move);
	if (((state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) && 
		(state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])) ||
		(!(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) && 
		!(state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])))
		env->move = 0;
	else if ((state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]))
		env->move = 1;
	else if ((state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]))
		env->move = -1;
	printf("%i ", env->move);
	if (abs(env->move) != 3 && state[SDL_SCANCODE_LSHIFT])
		env->move *= 3;
	else if (abs(env->move) == 3 && !state[SDL_SCANCODE_LSHIFT])
			env->move /= 3;
	printf("%i\n", env->move);
}

void	set_rot_flag(t_env *env, SDL_Event e, Uint8 *state)
{
	if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
		env->rot = 1;
	else if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
		env->rot = -1;
	else
		env->rot = 0;
	if (state[SDL_SCANCODE_LSHIFT])
		env->rot *= 2;
}

void	scan_keyboard(t_env *env, SDL_Event e)
{
	Uint8 *state;

	state = (Uint8*)SDL_GetKeyboardState(NULL);
	printf("%i\n", (state[SDL_SCANCODE_UP]
		|| state[SDL_SCANCODE_W] || state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]
		|| state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A] || state[SDL_SCANCODE_RIGHT]
		|| state[SDL_SCANCODE_D] || state[SDL_SCANCODE_LSHIFT]));
	if (e.type == SDL_KEYUP || e.type == SDL_KEYDOWN || state[SDL_SCANCODE_UP]
		|| state[SDL_SCANCODE_W] || state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]
		|| state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A] || state[SDL_SCANCODE_RIGHT]
		|| state[SDL_SCANCODE_D] || state[SDL_SCANCODE_LSHIFT])
	{
		set_move_flag(env, e, state);
		set_rot_flag(env, e, state);
	}
}