/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 12:59:46 by esuits            #+#    #+#             */
/*   Updated: 2018/10/05 13:02:11 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <SDL.h>
# include <SDL_image.h>
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
# define FOV 1.0471975512
# define NB_TILES 14
# define NB_TEXT 7
# define MAPPATH "maps/map04"

# define SAVE_FAIL "saving of map failed, path doesn't exist or no permission"
# define MALLOC_FAIL "not enough memory to malloc"
# define PARSE_ERR "error during parsing of map"
# define QUIT "byebye !"

typedef struct	s_text
{
	int			*map;
	int			img_w;
	int			img_h;
}				t_text;

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
	t_text		*texts;
	int			move;
	int			rot;
	int			ed;
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
void			print_wall(t_ray ray, t_env *env, int i, t_vec2 dir);
int				save_map(int **map, char *mapname);

int				color_tile(int n);
int				choose_color(SDL_Event e, t_env env, int prev);
t_text			choose_text(t_env *env, t_ray ray);

t_ray			init_ray(t_player player);
t_ray			intersect_wall(int **map, t_player player, t_ray ray);
void			send_rays(t_env *env);
int				ray_in_scop(t_ray ray);
double			wall_dist(t_ray ray, t_player player, t_vec2 dir);

Uint32			getpixel(SDL_Surface *surface, int x, int y);
void			cpy_px_map(t_text *texture, SDL_Surface *img);
t_text			get_texture_datas(char *path);
t_text			*get_texture(void);
int				uv_wall(t_text text, double x, double y);

int				detect_collision(t_env env, int dir);

int				*ft_strintsplit(char *str, char c);
int				**ft_intsplit(char **tab);
char			**ft_mise_en_tab(char *argv);
int				init_env(t_env *env, char **argv, int argc);
void			rescale(t_env *env);

void			move(t_env *env);
void			scan_keyboard(t_env *env, SDL_Event e);
void			scan_mouse(t_env *env, SDL_Event e);

void			ft_quit(t_env *env, char *str);

#endif
