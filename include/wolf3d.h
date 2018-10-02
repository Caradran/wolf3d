#ifndef WOLF3D_H
# define WOLF3D_H

# include <SDL.h>
# include "libmymath.h"
# include "libgraph.h"
# include "libft.h"
# include "libvec2.h"

# define WIDTH 1080
# define HEIGHT 900
# define BPP 32
# define TITLE "Wolf 3D"

# define NB_TILES 5

typedef struct  s_env
{
	SDL_Surface	*s;
	SDL_Window	*w;
	int			refresh;
	int 		**map;
	t_size		size;
	int 		scale;
}				t_env;

void	draw_legend(t_env *env);
void	draw_map(t_env *env);
void	draw_square_mouse(SDL_Event e, t_env *env, int flag);
void	save_map(int **map, char *mapname);

#endif