#ifndef LIBVEC2_H
# define LIBVEC2_H
# include <math.h>

typedef struct	s_vec2
{
	float x;
	float y;
}				t_vec2;

t_vec2	vec2_init(float x, float y);
t_vec2	vec2_add(t_vec2 a, t_vec2 b);
t_vec2	vec2_sub(t_vec2 a, t_vec2 b);
float	vec2_dot(t_vec2 a, t_vec2 b);
float	vec2_norme(t_vec2 a);
float	vec2_dist(t_vec2 a, t_vec2 b);
t_vec2	vec2_normalize(t_vec2 a);
t_vec2	vec2_scale(float a, t_vec2 vec);
t_vec2	vec2_rot(float a, t_vec2 vec);

#endif