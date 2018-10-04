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
	{0x555555, 0xffff00, 0x00ff00, 0xff0000, 0x050505, 0xffffff};

	return (colors[n]);
}

int		*ft_strintsplit(char *str, char c)
{
	int			*res;
	int			i;
	int			j;

	j = 0;
	i = 0;
	if (!str || !(res = (int*)malloc(sizeof(int) * 64)))
		return (NULL);
	while (j < 64)
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			j++;
		else
			return (NULL);
		if ((res[j - 1] = (int)ft_atoi(&(str[i]))) > NB_TILES || res[j - 1 ] < 0)
			return (NULL);
		while (str[i] && str[i] != c)
			i++;
		while (str[i] && str[i] == c)
			i++;
	}
	if (str[i])
		return (NULL);
	return (res);
}

int		**ft_intsplit(char **tab)
{
	int		**points;
	int		i;
	int		j;

	i = 0;
	if (!tab)
		return (NULL);
	if (!(points = malloc(sizeof(int*) * 64)))
		return (NULL);
	j = 0;
	while (j < 64)
	{
		if (!(points[j] = (int*)ft_strintsplit(tab[j], ' ')))
			return (NULL);
		j++;
		ft_memdel((void**)&tab[j - 1]);
	}
	ft_memdel((void**)&tab[j]);
	ft_memdel((void**)&tab);
	return (points);
}

char	**ft_mise_en_tab(char **argv)
{
	char	**buffer;
	int		i;
	int		fd;

	i = 0;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (NULL);
	if (!(buffer = malloc(sizeof(char *) * (65))))
		return (NULL);
	i = 0;
	while (get_next_line(fd, buffer + i) == 1 && i < 66)
		i++;
	if (i != 64)
		return (NULL);
	close(fd);
	return (buffer);
}

int		init_env(t_env *env, char **argv, int argc)
{
	int i;

	if (SDL_Init(SDL_INIT_VIDEO) || !(env->w = SDL_CreateWindow(TITLE,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)))
		return (1);
	if (argc == 2 && !(env->map = ft_intsplit(ft_mise_en_tab(argv))))
			ft_quit(env, PARSE_ERR);
	i = 0;
	if (argc == 1)
	{
		if (!(env->map = ft_memalloc(sizeof(int*) * 64)))
			ft_quit(env, MALLOC_FAIL);
		while (i < 64)
			if (!(env->map[i++] = ft_memalloc(sizeof(int) * 64)))
				ft_quit(env, MALLOC_FAIL);
	}
	env->player.pos = (t_vec2){1.5, 1.5};
	env->player.dir = vec2_normalize((t_vec2){1, 1});
	env->s = SDL_GetWindowSurface(env->w);
	env->size = (t_size){env->s->w, env->s->h};
	env->refresh = 1;
	env->texts = get_texture();
	rescale(env);
	return (0);
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

int		detect_collision(t_env env, int dir)
{
	int x;
	int y;
	int supp;

	x = env.player.pos.x + 0.1 * dir * env.player.dir.x;
	y = env.player.pos.y + 0.1 * dir * env.player.dir.y;
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
		while (SDL_PollEvent(&e))
		{
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
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP)
				if (!detect_collision(env, 1))
				{
					env.player.pos.x += env.player.dir.x * 0.1;
					env.player.pos.y += env.player.dir.y * 0.1;
					env.refresh = 1;
				}
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN)
				if (!detect_collision(env, -1))
				{
					env.player.pos.x -= env.player.dir.x * 0.1;
					env.player.pos.y -= env.player.dir.y * 0.1;
					env.refresh = 1;
				}
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT)
			{
				env.player.dir = vec2_rot(-M_PI / 90, env.player.dir);
				env.refresh = 1;
			}
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT)
			{
				env.player.dir = vec2_rot(M_PI / 90, env.player.dir);
				env.refresh = 1;
			}
		}
		if (env.refresh)
		{
			env.s = SDL_GetWindowSurface(env.w);
			bzero(env.s->pixels, sizeof(int) * env.s->w * env.s->h);
			if (argc == 1)
			{
				rescale(&env);
//				print_text(get_texture()[0], &env);
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
