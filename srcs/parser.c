/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 18:23:30 by esuits            #+#    #+#             */
/*   Updated: 2018/10/07 18:23:32 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
		if (!str[i] ||
			(res[j - 1] = ft_atoi(&(str[i]))) > NB_TILES || res[j - 1] < 0)
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

char	**ft_mise_en_tab(char *argv)
{
	char	**buffer;
	int		i;
	int		fd;

	i = 0;
	if ((fd = open(argv, O_RDONLY)) < 0)
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

void	init_flags(t_env *env)
{
	env->size = (t_size){env->s->w, env->s->h};
	env->refresh = 1;
	env->move = 0;
	env->rot = 0;
	env->ed = 0;
	env->player.pos = (t_vec2){1.5, 1.5};
	env->player.dir = vec2_normalize((t_vec2){1, 1});
	rescale(env);
}

int		init_env(t_env *env, char **argv, int argc)
{
	int i;

	if (SDL_Init(SDL_INIT_VIDEO) || !(env->w = SDL_CreateWindow(TITLE,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)))
		return (1);
	if (!(env->texts = get_texture()))
		exit(1);
	env->s = SDL_GetWindowSurface(env->w);
	init_flags(env);
	if (argc > 1 && !(env->map = ft_intsplit(ft_mise_en_tab(argv[1]))))
		ft_quit(env, PARSE_ERR);
	i = 0;
	if ((argc == 1 || argc == 3) && (env->ed = 1) && argc != 3)
	{
		if (!(env->map = ft_memalloc(sizeof(int*) * 64)))
			ft_quit(env, MALLOC_FAIL);
		while (i < 64)
			if (!(env->map[i++] = ft_memalloc(sizeof(int) * 64)))
				ft_quit(env, MALLOC_FAIL);
	}
	if (!env->ed && env->map[1][1])
		ft_quit(env, "block on player pos (1,1)");
	return (0);
}
