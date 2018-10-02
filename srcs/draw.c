#include "wolf3d.h"

void	draw_legend(t_env *env)
{
	int i;

	i = 0;
	while (i <= NB_TILES)
	{
		set_square(2 * env->scale, 0xffffff, (t_pos){68 * env->scale - 1, (i + NB_TILES / 2) * env->scale * 32 / NB_TILES - 1}, env->s);
		set_square(2 * env->scale - 2, color_tile(i), (t_pos){68 * env->scale, (i + NB_TILES / 2) * env->scale * 32 / NB_TILES}, env->s);
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
				set_square(env->scale - 1, color_tile(NB_TILES), (t_pos){i * env->scale, j * env->scale}, env->s);
			else if (env->map[j][i] >= 0 && env->map[j][i] <= NB_TILES)
				set_square(env->scale - 1, color_tile(env->map[j][i]), (t_pos){i * env->scale, j * env->scale}, env->s);
			j++;
		}
		i++;
	}
	draw_legend(env);
}

void	draw_square_mouse(SDL_Event e, t_env *env, int flag)
{
	if (e.motion.x/env->scale < 63 && e.motion.y/env->scale < 63 &&
		e.motion.x/env->scale > 0 && e.motion.y/env->scale > 0)
	{
		env->map[((int)(e.motion.y/env->scale))][((int)(e.motion.x/env->scale))] = flag;
		env->refresh = 1;
	}
}