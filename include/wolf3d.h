#ifndef WOLF3D_H
# define WOLF3D_H

# include <SDL.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libmymath.h"
# include "libgraph.h"
# include "libft.h"
# include "libvec2.h"
# include <math.h>
# include "get_next_line.h"

# define WIDTH 1080
# define HEIGHT 900
# define BPP 32
# define TITLE "Wolf 3D"
# define FOV M_PI / 3.0
# define NB_TILES 5

typedef struct	s_player
{
	t_vec2		pos;
	t_vec2		dir;
}				t_player;

typedef struct	s_env
{
	SDL_Surface	*s;
	SDL_Window	*w;
	int			refresh;
	int			**map;
	t_size		size;
	int			scale;
	t_player	player;
}				t_env;

typedef struct	s_ray
{
	int			pos_x;
	int			pos_y;
	int			side;
	t_vec2		dir;
	t_vec2		dist;
	t_vec2		delta;
}				t_ray;

void			draw_legend(t_env *env);
void			draw_map(t_env *env);
void			draw_square_mouse(SDL_Event e, t_env *env, int flag);
void			save_map(int **map, char *mapname);

int				color_tile(int n);

t_ray			init_ray(t_player player);
t_ray			intersect_wall(int **map, t_player player, t_ray ray);
void			send_rays(t_env *env);

#endif
